/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_resource.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:31:43 by junji             #+#    #+#             */
/*   Updated: 2023/01/20 16:56:22 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_rest(t_philosophy *philosophy)
{
	free(philosophy[0].shared_data->m_fork);
	free(philosophy[0].shared_data->m_print);
	free(philosophy[0].shared_data->m_is_all_eat);
	free(philosophy[0].shared_data->m_last_eat_time);
	free(philosophy[0].shared_data->is_print_possible);
	free(philosophy[0].shared_data->fork_state);
	free(philosophy[0].shared_data->is_all_eat);
	free(philosophy[0].shared_data->last_eat_time);
	free(philosophy[0].shared_data);
	free(philosophy);
}

int	wait_thread(t_philosophy *philosophy, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (_pthread_join(philosophy[i].thread, NULL) == 1)
			return (1);
	}
	return (0);
}

int	return_resource(t_philosophy *philosophy)
{
	const int		n = philosophy->philo_character->number_of_philosophers;
	int				i;
	t_shared_data	*shared_data;

	shared_data = philosophy[0].shared_data;
	if (wait_thread(philosophy, n) == 1)
		return (1);
	if (_pthread_mutex_destroy(&shared_data->m_is_anyone_die) == 1)
		return (1);
	i = -1;
	shared_data = philosophy[0].shared_data;
	while (++i < n)
	{
		if (_pthread_mutex_destroy(&shared_data->m_fork[i]) == 1)
			return (1);
		if (_pthread_mutex_destroy(&shared_data->m_print[i]) == 1)
			return (1);
		if (_pthread_mutex_destroy(&shared_data->m_is_all_eat[i]) == 1)
			return (1);
		if (_pthread_mutex_destroy(&shared_data->m_last_eat_time[i]) == 1)
			return (1);
	}
	free_rest(philosophy);
	return (0);
}
