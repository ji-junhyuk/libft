/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:36:09 by junji             #+#    #+#             */
/*   Updated: 2023/01/19 17:11:14 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_thinking(t_philosophy *philo)
{
	t_shared_data	*shared_data;

	shared_data = philo->shared_data;
	if (is_anyone_die_true(shared_data))
		return (1);
	print_elapse_time(philo, "is thinking", false);
	usleep(100);
	return (0);
}

int	get_fork(t_philosophy *philo)
{
	const int		identity = philo->identity;
	const int		n = philo->philo_character->number_of_philosophers;
	const int		right_fork = (identity + n - 1) % n;
	t_shared_data	*shared_data;

	shared_data = philo->shared_data;
	if (identity == right_fork)
		return (msleep(philo->philo_character->time_to_die));
	if (is_anyone_die_true(shared_data))
		return (1);
	if (identity % 2 == 0)
	{
		if (_pthread_mutex_lock(&shared_data->m_fork[identity]) == 1)
			return (-1);
		shared_data->fork_state[identity] = true;
		if (_pthread_mutex_lock(&shared_data->m_fork[right_fork]) == 1)
			return (-1);
		shared_data->fork_state[right_fork] = true;
		return (print_elapse_time(philo, "has taken a fork", true));
	}
	if (_pthread_mutex_lock(&shared_data->m_fork[right_fork]) == 1)
		return (-1);
	if (_pthread_mutex_lock(&shared_data->m_fork[identity]) == 1)
		return (-1);
	shared_data->fork_state[right_fork] = true;
	shared_data->fork_state[identity] = true;
	return (print_elapse_time(philo, "has taken a fork", true));
}

int	eat_spaghetti(t_philosophy *philo, int eat_count)
{
	const int		eat_time = philo->philo_character->time_to_eat;
	const int		identity = philo->identity;
	t_shared_data	*shared_data;

	shared_data = philo->shared_data;
	if (is_anyone_die_true(shared_data))
		return (1);
	print_elapse_time(philo, "is eating", true);
	if (eat_count == 0)
	{
		_pthread_mutex_lock(&philo->shared_data->m_is_all_eat[identity]);
		philo->shared_data->is_all_eat[identity] = true;
		_pthread_mutex_unlock(&philo->shared_data->m_is_all_eat[identity]);
	}
	msleep(eat_time);
	return (0);
}

int	putdown_fork(t_philosophy *philo)
{
	const int		identity = philo->identity;
	const int		n = philo->philo_character->number_of_philosophers;
	const int		left_fork = identity;
	const int		right_fork = (identity + n - 1) % n;
	t_shared_data	*shared_data;

	shared_data = philo->shared_data;
	if (is_anyone_die_true(shared_data))
		return (1);
	if (identity % 2 == 0)
	{
		if (_pthread_mutex_unlock(&shared_data->m_fork[left_fork]))
			return (-1);
		if (_pthread_mutex_unlock(&shared_data->m_fork[right_fork]) == 1)
			return (-1);
		shared_data->fork_state[left_fork] = false;
		shared_data->fork_state[right_fork] = false;
		return (0);
	}
	if (_pthread_mutex_unlock(&shared_data->m_fork[right_fork]) == 1)
		return (-1);
	if (_pthread_mutex_unlock(&shared_data->m_fork[left_fork]) == 1)
		return (-1);
	shared_data->fork_state[right_fork] = false;
	shared_data->fork_state[left_fork] = false;
	return (0);
}

int	is_sleeping(t_philosophy *philo)
{
	const int		sleep_time = philo->philo_character->time_to_sleep;
	t_shared_data	*shared_data;

	shared_data = philo->shared_data;
	if (_pthread_mutex_lock(&shared_data->m_is_anyone_die) == 1)
		return (-1);
	if (shared_data->is_anyone_die == true)
	{
		if (_pthread_mutex_unlock(&shared_data->m_is_anyone_die) == 1)
			return (-1);
		return (1);
	}
	if (_pthread_mutex_unlock(&shared_data->m_is_anyone_die) == 1)
		return (-1);
	print_elapse_time(philo, "is sleeping", false);
	msleep(sleep_time);
	return (0);
}
