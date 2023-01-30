/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:26:14 by junji             #+#    #+#             */
/*   Updated: 2023/01/30 08:59:31 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_shared_data(t_shared_data *shared, int n)
{
	int		i;
	bool	sys_failed;

	sys_failed = false;
	shared->is_anyone_die = false;
	sys_failed |= _pthread_mutex_init(&shared->m_is_anyone_die, NULL);
	i = -1;
	while (++i < n)
	{
		shared->fork_state[i] = false;
		shared->is_print_possible[i] = true;
		shared->is_all_eat[i] = false;
		shared->last_eat_time[i] = 0;
		sys_failed |= _pthread_mutex_init(&shared->m_fork[i], NULL);
		sys_failed |= _pthread_mutex_init(&shared->m_print[i], NULL);
		sys_failed |= _pthread_mutex_init(&shared->m_is_all_eat[i], NULL);
		sys_failed |= _pthread_mutex_init(&shared->m_last_eat_time[i], NULL);
	}
	if (sys_failed)
		return (1);
	return (0);
}

int	malloc_shared_data(t_shared_data **shared_data, int n)
{
	(*shared_data)->m_fork = _malloc(sizeof(pthread_mutex_t) * n);
	if (!(*shared_data)->m_fork)
		return (1);
	(*shared_data)->fork_state = _malloc(sizeof(bool) * n);
	if (!(*shared_data)->fork_state)
		return (1);
	(*shared_data)->m_print = _malloc(sizeof(pthread_mutex_t) * n);
	if (!(*shared_data)->m_print)
		return (1);
	(*shared_data)->is_print_possible = _malloc(sizeof(bool) * n);
	if (!(*shared_data)->is_print_possible)
		return (1);
	(*shared_data)->m_is_all_eat = _malloc(sizeof(pthread_mutex_t) * n);
	if (!(*shared_data)->m_is_all_eat)
		return (1);
	(*shared_data)->is_all_eat = _malloc(sizeof(bool) * n);
	if (!(*shared_data)->is_all_eat)
		return (1);
	(*shared_data)->m_last_eat_time = _malloc(sizeof(pthread_mutex_t) * n);
	if (!(*shared_data)->m_last_eat_time)
		return (1);
	(*shared_data)->last_eat_time = _malloc(sizeof(long) * n);
	if (!(*shared_data)->last_eat_time)
		return (1);
	return (0);
}

int	init_struct(t_philosophy **philosophy,
	t_philo_character *philo_character, int i)
{
	const int		n = philo_character->number_of_philosophers;
	struct timeval	start_time;
	t_shared_data	*shared_data;

	*philosophy = _malloc(sizeof(t_philosophy) * n);
	if (!*philosophy)
		return (1);
	shared_data = _malloc(sizeof(t_shared_data));
	if (!shared_data)
		return (1);
	if (malloc_shared_data(&shared_data, n) == 1)
		return (1);
	if (init_shared_data(shared_data, n) == 1)
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
