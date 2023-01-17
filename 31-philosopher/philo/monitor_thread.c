/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:33:21 by junji             #+#    #+#             */
/*   Updated: 2023/01/17 14:34:08 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_philo_dead(t_philosophy *philo)
{
	int			i;
	int			fasting_time;
	long		passed_time_start;
	const int	numbers = philo->philo_character->number_of_philosophers;
	const int	time_to_die = philo->philo_character->time_to_die;

	i = -1;
	while (++i < numbers)
	{
		passed_time_start = get_elapsed_milesecond(&philo[i], false);
		_pthread_mutex_lock(&(philo[i].shared_data->m_last_eat_time));
		fasting_time = passed_time_start - philo[i].shared_data->last_eat_time;
		if (fasting_time >= time_to_die)
		{
			_pthread_mutex_lock(&philo[i].shared_data->m_is_anyone_die);
			philo[i].shared_data->is_anyone_die = true;
			_pthread_mutex_unlock(&philo[i].shared_data->m_is_anyone_die);
			_pthread_mutex_unlock(&(philo[i].shared_data->m_last_eat_time));
			print_elapse_time(&philo[i], "died", false);
			return (true);
		}
		_pthread_mutex_unlock(&(philo[i].shared_data->m_last_eat_time));
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
