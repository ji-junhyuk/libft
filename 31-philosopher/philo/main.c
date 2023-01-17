/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:43:32 by junji             #+#    #+#             */
/*   Updated: 2023/01/17 15:28:40 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine(t_philosophy *philosophy, int identity, int eat_count, int numbers)
{
	const int	left_fork = identity;
	const int	right_fork = (identity + numbers - 1) % numbers;

	while (--eat_count >= 0)
	{
		if (is_thinking(philosophy))
			return (1);
		if (get_fork(philosophy))
			return (1);
		if (eat_spaghetti(philosophy))
		{
			pthread_mutex_unlock(&philosophy->shared_data->m_fork[right_fork]);
			pthread_mutex_unlock(&philosophy->shared_data->m_fork[left_fork]);
			return (1);
		}
		if (putdown_fork(philosophy))
		{
			pthread_mutex_unlock(&philosophy->shared_data->m_fork[right_fork]);
			pthread_mutex_unlock(&philosophy->shared_data->m_fork[left_fork]);
			return (1);
		}
		if (is_sleeping(philosophy))
			return (1);
	}
	return (0);
}

void	*dining_philosopher(void *philo)
{
	t_philosophy	*philosophy;
	int				identity;
	int				eat_count;
	int				numbers;
	int				sleep_time;

	philosophy = (t_philosophy *)philo;
	identity = philosophy->identity;
	eat_count = philosophy->philo_character->must_eat;
	sleep_time = philosophy->philo_character->time_to_sleep;
	numbers = philosophy->philo_character->number_of_philosophers;
	if (identity % 2 == 0)
		msleep(sleep_time);
	if (routine(philosophy, identity, eat_count, numbers) == 1)
		return (NULL);
	pthread_mutex_lock(&philosophy->shared_data->m_is_all_eat);
	philosophy->shared_data->is_all_eat = true;
	pthread_mutex_unlock(&philosophy->shared_data->m_is_all_eat);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_philo_character	philo_character;
	t_philosophy		*philosophy;

	philosophy = NULL;
	if (!is_valid_input(argc, (const char **)argv, &philo_character))
		return (1);
	if (create_philosophers(&philosophy, &philo_character) == 1)
		return (1);
	if (monitor_philosophers(philosophy) == 1)
		return (1);
	return (return_resource(philosophy));
}
