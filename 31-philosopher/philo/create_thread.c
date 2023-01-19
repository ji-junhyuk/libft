/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:26:14 by junji             #+#    #+#             */
/*   Updated: 2023/01/19 16:47:54 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_shared_data(t_shared_data *shared_data, int n)
{
	int		i;
	bool	syscall_failed;

	syscall_failed = false;
	shared_data->is_anyone_die = false;
	syscall_failed |= _pthread_mutex_init(&shared_data->m_is_anyone_die, NULL);
	i = -1;
	while (++i < n)
	{
		shared_data->fork_state[i] = false;
		shared_data->is_print_possible[i] = true;
		shared_data->is_all_eat[i] = false;
		shared_data[i].last_eat_time = 0;
		syscall_failed |= _pthread_mutex_init(&shared_data->m_fork[i], NULL);
		syscall_failed |= _pthread_mutex_init(&shared_data->m_print[i], NULL);
		syscall_failed |= _pthread_mutex_init(&shared_data->m_is_all_eat[i], NULL);
		syscall_failed |= _pthread_mutex_init(&shared_data->m_last_eat_time[i], NULL);
	}
	if (syscall_failed)
		return (1);
	return (0);
}

int	malloc_shared_data(t_shared_data **shared_data_addr, int n)
{
	t_shared_data		*shared_data;

	shared_data = _malloc(sizeof(t_shared_data) * n);
	shared_data->m_fork = _malloc(sizeof(pthread_mutex_t) * n);
	shared_data->fork_state = _malloc(sizeof(bool) * n);
	shared_data->m_print = _malloc(sizeof(pthread_mutex_t) * n);
	shared_data->is_print_possible = _malloc(sizeof(bool) * n);
	shared_data->m_is_all_eat = _malloc(sizeof(pthread_mutex_t) * n);
	shared_data->is_all_eat = _malloc(sizeof(bool) * n);
	shared_data->m_last_eat_time = _malloc(sizeof(pthread_mutex_t) * n);
	shared_data->last_eat_time = _malloc(sizeof(long) * n);
	if (init_shared_data(shared_data, n) == 1)
		return (1);
	*shared_data_addr = shared_data;
	return (0);
}

int	init_struct(t_philosophy **philosophy,
	t_philo_character *philo_character, int i)
{
	const int		n = philo_character->number_of_philosophers;
	struct timeval	start_time;
	t_shared_data	*shared_data;

	shared_data = NULL;
	*philosophy = _malloc(sizeof(t_philosophy) * n);
	if (!*philosophy)
		return (1);
	if (malloc_shared_data(&shared_data, n) == 1)
		return (1);
	i = -1;
	gettimeofday(&start_time, NULL);
	while (++i < n)
	{
		(*philosophy)[i].identity = i;
		(*philosophy)[i].philo_character = philo_character;
		(*philosophy)[i].shared_data = shared_data;
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
