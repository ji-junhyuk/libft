/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:23:38 by junji             #+#    #+#             */
/*   Updated: 2023/01/17 14:25:06 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_valid_number(const int argc, const char *argv[],
		t_philo_character *philo_char)
{
	philo_char->number_of_philosophers = ft_atoi(argv[1]);
	philo_char->time_to_die = ft_atoi(argv[2]);
	philo_char->time_to_eat = ft_atoi(argv[3]);
	philo_char->time_to_sleep = ft_atoi(argv[4]);
	philo_char->must_eat = 0x7fffffff;
	if (philo_char->number_of_philosophers <= 0)
		return (false);
	if (philo_char->time_to_die < 0 || philo_char->time_to_eat < 0
		|| philo_char->time_to_sleep < 0)
		return (false);
	if (argc == 6)
	{
		philo_char->must_eat = ft_atoi(argv[5]);
		if (philo_char->must_eat < 0)
			return (false);
	}
	return (true);
}

bool	is_valid_input(const int argc, const char *argv[],
		t_philo_character *philo_char)
{
	const char	*input_argc_error_msg = "usage: \n\
1. number_of_philosophers\n\
2. time_to_die(in milliseconds\n\
3. time_to_eat(in milliseconds\n\
4. time_to_sleep(in milliseconds\n\
5. number_of_times_each_philosopher_must_eat(optional argument\n\
*input number follow atoi rule";
	const char	*input_number_error_msg = "usage: \n\
1. philosopher more than 0\n\
2. negative argument is not allowed\n\
*input number follow atoi rule";

	memset(philo_char, 0, sizeof(*philo_char));
	if (!(argc == 5 || argc == 6))
	{
		ft_putstr_fd(input_argc_error_msg, 2);
		return (false);
	}
	if (!is_valid_number(argc, argv, philo_char))
	{
		ft_putstr_fd(input_number_error_msg, 2);
		return (false);
	}
	return (true);
}
