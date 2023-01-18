/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:26:14 by junji             #+#    #+#             */
/*   Updated: 2023/01/18 15:59:44 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_shared_data *shared_data, int identity)
{
	if (_pthread_mutex_init(&shared_data->m_is_all_eat, NULL) == 1)
		return (1);
	if (_pthread_mutex_init(&shared_data->m_is_anyone_die, NULL) == 1)
		return (1);
	if (_pthread_mutex_init(&shared_data->m_last_eat_time, NULL) == 1)
		return (1);
	if (_pthread_mutex_init(&shared_data->m_fork[identity], NULL) == 1)
		return (1);
	if (_pthread_mutex_init(&shared_data->m_print[identity], NULL) == 1)
		return (1);
	return (0);
}

int	init_shared_data(t_shared_data *shared_data, pthread_mutex_t *m_print,
	pthread_mutex_t *m_fork, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		shared_data[i].m_print = m_print;
		shared_data[i].m_fork = m_fork;
		shared_data[i].is_print_possible = true;
		shared_data[i].is_all_eat = false;
		shared_data[i].is_anyone_die = false;
		shared_data[i].last_eat_time = 0;
		if (init_mutex(&shared_data[i], i) == 1)
			return (1);
	}
	return (0);
}

int	malloc_struct(t_shared_data **shared_data_addr,
	pthread_mutex_t **m_fork_addr, pthread_mutex_t **m_print_addr, int n)
{
	t_shared_data		*shared_data;
	pthread_mutex_t		*m_fork;
	pthread_mutex_t		*m_print;

	shared_data = _malloc(sizeof(t_shared_data) * n);
	if (!shared_data)
		return (1);
	m_fork = _malloc(sizeof(pthread_mutex_t) * n);
	if (!m_fork)
		return (1);
	m_print = _malloc(sizeof(pthread_mutex_t) * n);
	if (!m_print)
		return (1);
	*shared_data_addr = shared_data;
	*m_fork_addr = m_fork;
	*m_print_addr = m_print;
	if (init_shared_data(shared_data, m_print, m_fork, n) == 1)
		return (1);
	return (0);
}

int	init_struct(t_philosophy **philosophy,
	t_philo_character *philo_character, int i)
{
	const int		n = philo_character->number_of_philosophers;
	struct timeval	start_time;
	t_shared_data	*shared_data;
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	*m_print;

	shared_data = NULL;
	m_fork = NULL;
	m_print = NULL;
	*philosophy = _malloc(sizeof(t_philosophy) * n);
	if (!*philosophy)
		return (1);
	if (malloc_struct(&shared_data, &m_fork, &m_print, n) == 1)
		return (1);
	i = -1;
	gettimeofday(&start_time, NULL);
	while (++i < n)
	{
		(*philosophy)[i].identity = i;
		(*philosophy)[i].philo_character = philo_character;
		(*philosophy)[i].shared_data = &shared_data[i];
		(*philosophy)[i].start_time = start_time;
	}
	return (0);
}

int	create_philosophers(t_philosophy **philosophy,
	t_philo_character *philo_character)
{
	int	i;

	i = -1;
	init_struct(philosophy, philo_character, i);
	while (++i < philo_character->number_of_philosophers)
	{
		if (_pthread_create(&((*philosophy)[i].thread), NULL,
			dining_philosopher, &(*philosophy)[i]) == 1)
			return (1);
	}
	return (0);
}
