/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:36:09 by junji             #+#    #+#             */
/*   Updated: 2023/01/30 09:48:43 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_thinking(t_philosophy *philo, int n)
{
	t_shared_data	*shared_data;

	shared_data = philo->shared_data;
	if (is_anyone_die_true(shared_data))
		return (1);
	print_elapse_time(philo, "is thinking", false);
	if (n == 1)
		return (msleep(philo->philo_character->time_to_die));
	return (0);
}

int	get_fork(t_philosophy *philo, int identity, int n, bool sys_failed)
{
	const int		right_fork = (identity + n - 1) % n;
	t_shared_data	*shared_data;

	shared_data = philo->shared_data;
	if (is_anyone_die_true(shared_data))
		return (1);
	if (identity % 2 == 0)
	{
		sys_failed |= _pthread_mutex_lock(&shared_data->m_fork[identity]);
		shared_data->fork_state[identity] = true;
		print_elapse_time(philo, "has taken a fork", false);
		sys_failed |= _pthread_mutex_lock(&shared_data->m_fork[right_fork]);
		shared_data->fork_state[right_fork] = true;
		if (sys_failed)
			return (-1);
		return (print_elapse_time(philo, "has taken a fork", false));
	}
	sys_failed |= _pthread_mutex_lock(&shared_data->m_fork[right_fork]);
	sys_failed |= _pthread_mutex_lock(&shared_data->m_fork[identity]);
	shared_data->fork_state[right_fork] = true;
	print_elapse_time(philo, "has taken a fork", false);
	shared_data->fork_state[identity] = true;
	if (sys_failed)
		return (-1);
	return (print_elapse_time(philo, "has taken a fork", false));
}

int	eat_spaghetti(t_philosophy *philo, int eat_count, bool sys_failed)
{
	const int		eat_time = philo->philo_character->time_to_eat;
	const int		identity = philo->identity;
	t_shared_data	*shared;

	shared = philo->shared_data;
	if (is_anyone_die_true(shared))
		return (1);
	print_elapse_time(philo, "is eating", true);
	if (eat_count == 0)
	{
		sys_failed |= _pthread_mutex_lock(&shared->m_is_all_eat[identity]);
		shared->is_all_eat[identity] = true;
		sys_failed |= _pthread_mutex_unlock(&shared->m_is_all_eat[identity]);
	}
	if (sys_failed)
		return (-1);
	msleep(eat_time);
	return (0);
}

int	putdown_fork(t_philosophy *philo, bool sys_failed)
{
	const int		identity = philo->identity;
	const int		n = philo->philo_character->number_of_philosophers;
	const int		right_fork = (identity + n - 1) % n;
	t_shared_data	*shared_data;

	shared_data = philo->shared_data;
	if (is_anyone_die_true(shared_data))
		return (1);
	if (identity % 2 == 0)
	{
		shared_data->fork_state[identity] = false;
		sys_failed |= _pthread_mutex_unlock(&shared_data->m_fork[identity]);
		usleep(100);
		shared_data->fork_state[right_fork] = false;
		sys_failed |= _pthread_mutex_unlock(&shared_data->m_fork[right_fork]);
		return (0);
	}
	shared_data->fork_state[identity] = false;
	sys_failed |= _pthread_mutex_unlock(&shared_data->m_fork[identity]);
	usleep(100);
	shared_data->fork_state[right_fork] = false;
	sys_failed |= pthread_mutex_unlock(&shared_data->m_fork[right_fork]);
	if (sys_failed)
		return (-1);
	return (0);
}

int	is_sleeping(t_philosophy *philo, bool sys_failed)
{
	const int		sleep_time = philo->philo_character->time_to_sleep;
	t_shared_data	*shared_data;

	shared_data = philo->shared_data;
	sys_failed |= _pthread_mutex_lock(&shared_data->m_is_anyone_die);
	if (shared_data->is_anyone_die == true)
	{
		sys_failed |= _pthread_mutex_unlock(&shared_data->m_is_anyone_die);
		return (1);
	}
	sys_failed |= pthread_mutex_unlock(&shared_data->m_is_anyone_die);
	if (sys_failed)
		return (-1);
	print_elapse_time(philo, "is sleeping", false);
	msleep(sleep_time);
	return (0);
}
