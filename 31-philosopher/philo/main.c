/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:43:32 by junji             #+#    #+#             */
/*   Updated: 2023/01/30 09:41:16 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine(t_philosophy *philo, int identity, int eat_count, int n)
{
	const int	left_fork = identity;
	const int	right_fork = (identity + n - 1) % n;

	while (--eat_count >= 0)
	{
		if (is_thinking(philo, n))
			return (1);
		if (get_fork(philo, identity, n, false))
			return (1);
		if (eat_spaghetti(philo, eat_count, false))
		{
			_pthread_mutex_unlock(&philo->shared_data->m_fork[right_fork]);
			_pthread_mutex_unlock(&philo->shared_data->m_fork[left_fork]);
			return (1);
		}
		if (putdown_fork(philo, false))
		{
			_pthread_mutex_unlock(&philo->shared_data->m_fork[right_fork]);
			_pthread_mutex_unlock(&philo->shared_data->m_fork[left_fork]);
			return (1);
		}
		if (is_sleeping(philo, false))
			return (1);
	}
	return (0);
}

void	*dining_philosopher(void *philosophy)
{
	t_philosophy	*philo;
	int				numbers;
	int				sleep_time;
	bool			sys_failed;
	t_shared_data	*shared_data;

	philo = (t_philosophy *)philosophy;
	shared_data = philo->shared_data;
	sleep_time = philo->philo_character->time_to_eat;
	numbers = philo->philo_character->number_of_philosophers;
	sys_failed = false;
	if (philo->philo_character->must_eat == 0)
	{
		_pthread_mutex_lock(&shared_data->m_is_all_eat[philo->identity]);
		shared_data->is_all_eat[philo->identity] = true;
		_pthread_mutex_unlock(&shared_data->m_is_all_eat[philo->identity]);
		return (NULL);
	}
	if (philo->identity % 2 == 0)
		msleep(sleep_time / 100);
	if (routine(philo, philo->identity,
			philo->philo_character->must_eat, numbers) == 1)
		return (NULL);
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
