/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:33:21 by junji             #+#    #+#             */
/*   Updated: 2023/01/20 11:40:37 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_anyone_die_true(t_shared_data *shared_data)
{
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
	return (0);
}

int	is_anyone_die(t_philosophy *philo, int identity)
{
	const int		time_to_die = philo->philo_character->time_to_die;
	long			passed_time_start;
	long			fasting_time;
	t_shared_data	*shared_data;

	shared_data = philo[identity].shared_data;
	passed_time_start = get_elapsed_milesecond(&philo[identity], false);
	_pthread_mutex_lock(&shared_data->m_last_eat_time[identity]);
	fasting_time = passed_time_start - shared_data->last_eat_time[identity];
	_pthread_mutex_unlock(&shared_data->m_last_eat_time[identity]);
	if (fasting_time >= time_to_die)
	{
		_pthread_mutex_lock(&shared_data->m_is_anyone_die);
		shared_data->is_anyone_die = true;
		_pthread_mutex_unlock(&shared_data->m_is_anyone_die);
		print_elapse_time(&philo[identity], "died", false);
		_pthread_mutex_lock(&shared_data->m_print[identity]);
		philo[identity].shared_data->is_print_possible = false;
		_pthread_mutex_unlock(&shared_data->m_print[identity]);
		return (true);
	}
	_pthread_mutex_unlock(&shared_data->m_last_eat_time[identity]);
	return (false);
}

bool	is_philo_dead(t_philosophy *philo)
{
	int			i;
	const int	numbers = philo->philo_character->number_of_philosophers;

	i = -1;
	while (++i < numbers)
	{
		if (is_anyone_die(philo, i))
			return (true);
	}
	return (false);
}

bool	is_all_finished_dining(t_philosophy *philo)
{
	const int	n = philo->philo_character->number_of_philosophers;
	int			i;

	i = -1;
	while (++i < n)
	{
		_pthread_mutex_lock(&(philo[i].shared_data->m_is_all_eat[i]));
		if (philo[i].shared_data->is_all_eat[i] == false)
		{
			_pthread_mutex_unlock(&(philo[i].shared_data->m_is_all_eat[i]));
			return (false);
		}
		_pthread_mutex_unlock(&(philo[i].shared_data->m_is_all_eat[i]));
	}
	return (true);
}

int	monitor_philosophers(t_philosophy *philo)
{
	while (1)
	{
		if (is_philo_dead(philo))
			return (0);
		if (is_all_finished_dining(philo))
			return (0);
	}
}
