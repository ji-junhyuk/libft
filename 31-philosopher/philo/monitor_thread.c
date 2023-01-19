/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:33:21 by junji             #+#    #+#             */
/*   Updated: 2023/01/19 11:37:36 by junji            ###   ########.fr       */
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
	_pthread_mutex_lock(&shared_data->m_last_eat_time);
	fasting_time = passed_time_start - shared_data->last_eat_time;
	_pthread_mutex_unlock(&shared_data->m_last_eat_time);
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
	_pthread_mutex_unlock(&shared_data->m_last_eat_time);
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

bool	is_all_finished_dining(t_philosophy *philosophy)
{
	const int	n = philosophy->philo_character->number_of_philosophers;
	int			i;

	i = -1;
	while (++i < n)
	{
		_pthread_mutex_lock(&(philosophy[i].shared_data->m_is_all_eat));
		if (philosophy[i].shared_data->is_all_eat == false)
		{
			_pthread_mutex_unlock(&(philosophy[i].shared_data->m_is_all_eat));
			return (false);
		}
		_pthread_mutex_unlock(&(philosophy[i].shared_data->m_is_all_eat));
	}
	return (true);
}

int	monitor_philosophers(t_philosophy *philosophy)
{
	const int		n = philosophy->philo_character->number_of_philosophers;
	int				i;
	t_shared_data	*cur_shared_data;

	while (1)
	{
		if (is_philo_dead(philosophy))
		{
			i = -1;
			while (++i < n)
			{
				cur_shared_data = philosophy[i].shared_data;
				_pthread_mutex_lock(&cur_shared_data->m_is_anyone_die);
				philosophy[i].shared_data->is_anyone_die = true;
				_pthread_mutex_unlock(&cur_shared_data->m_is_anyone_die);
			}
			return (0);
		}
		if (is_all_finished_dining(philosophy))
			return (0);
	}
}
