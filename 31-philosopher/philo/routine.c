/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:36:09 by junji             #+#    #+#             */
/*   Updated: 2023/01/19 11:48:45 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_thinking(t_philosophy *philosophy)
{
	t_shared_data	*cur_shared_data;

	cur_shared_data = philosophy->shared_data;
	if (is_anyone_die_true(cur_shared_data))
		return (1);
	print_elapse_time(philosophy, "is thinking", false);
	return (0);
}

int	get_fork(t_philosophy *philosophy)
{
	const int		identity = philosophy->identity;
	const int		n = philosophy->philo_character->number_of_philosophers;
	const int		right_fork = (identity + n - 1) % n;
	t_shared_data	*cur_shared_data;

	cur_shared_data = philosophy->shared_data;
	if (identity == right_fork)
		return (msleep(philosophy->philo_character->time_to_die));
	if (is_anyone_die_true(cur_shared_data))
		return (1);
	if (identity % 2 == 0)
	{
		if (_pthread_mutex_lock(&cur_shared_data->m_fork[identity]) == 1)
			return (-1);
		if (_pthread_mutex_lock(&cur_shared_data->m_fork[right_fork]) == 1)
			return (-1);
	}
	else
	{
		if (_pthread_mutex_lock(&cur_shared_data->m_fork[right_fork]) == 1)
			return (-1);
		if (_pthread_mutex_lock(&cur_shared_data->m_fork[identity]) == 1)
			return (-1);
	}
	return (print_elapse_time(philosophy, "has taken a fork", true));
}

int	eat_spaghetti(t_philosophy *philosophy, int eat_count)
{
	const int		eat_time = philosophy->philo_character->time_to_eat;
	t_shared_data	*cur_shared_data;

	cur_shared_data = philosophy->shared_data;
	if (is_anyone_die_true(cur_shared_data))
		return (1);
	print_elapse_time(philosophy, "is eating", true);
	if (eat_count == 0)
	{
		_pthread_mutex_lock(&philosophy->shared_data->m_is_all_eat);
		philosophy->shared_data->is_all_eat = true;
		_pthread_mutex_unlock(&philosophy->shared_data->m_is_all_eat);
	}
	msleep(eat_time);
	return (0);
}

int	putdown_fork(t_philosophy *philosophy)
{
	const int		identity = philosophy->identity;
	const int		n = philosophy->philo_character->number_of_philosophers;
	const int		left_fork = identity;
	const int		right_fork = (identity + n - 1) % n;
	t_shared_data	*cur_shared_data;

	cur_shared_data = philosophy->shared_data;
	if (is_anyone_die_true(cur_shared_data))
		return (1);
	if (identity % 2 == 0)
	{
		if (_pthread_mutex_unlock(&cur_shared_data->m_fork[left_fork]))
			return (-1);
		if (_pthread_mutex_unlock(&cur_shared_data->m_fork[right_fork]) == 1)
			return (-1);
		return (0);
	}
	if (_pthread_mutex_unlock(&cur_shared_data->m_fork[right_fork]) == 1)
		return (-1);
	if (_pthread_mutex_unlock(&cur_shared_data->m_fork[left_fork]) == 1)
		return (-1);
	return (0);
}

int	is_sleeping(t_philosophy *philosophy)
{
	const int		sleep_time = philosophy->philo_character->time_to_sleep;
	t_shared_data	*cur_shared_data;

	cur_shared_data = philosophy->shared_data;
	if (_pthread_mutex_lock(&cur_shared_data->m_is_anyone_die) == 1)
		return (-1);
	if (cur_shared_data->is_anyone_die == true)
	{
		if (_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die) == 1)
			return (-1);
		return (1);
	}
	if (_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die) == 1)
		return (-1);
	print_elapse_time(philosophy, "is sleeping", false);
	msleep(sleep_time);
	return (0);
}
