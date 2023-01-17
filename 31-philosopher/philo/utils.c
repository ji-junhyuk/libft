/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:20:23 by junji             #+#    #+#             */
/*   Updated: 2023/01/17 14:47:43 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	msleep(int time)
{
	struct timeval	cur_time;
	long			start_sec;
	int				start_usec;
	int				waiting_time;

	gettimeofday(&cur_time, NULL);
	start_sec = cur_time.tv_sec;
	start_usec = cur_time.tv_usec;
	waiting_time = 0;
	while (waiting_time < time)
	{
		gettimeofday(&cur_time, NULL);
		waiting_time = (cur_time.tv_sec - start_sec) * 1000
			+ (cur_time.tv_usec - start_usec) / 1000;
		usleep(100);
	}
	return (0);
}

long	get_elapsed_milesecond(t_philosophy *philosophy, bool is_eat_status)
{
	struct timeval	cur_time;
	long			elapsed_time;
	long			sec;
	int				usec;
	t_shared_data	*cur_shared_data;

	gettimeofday(&cur_time, NULL);
	cur_shared_data = philosophy->shared_data;
	sec = (cur_time.tv_sec - philosophy->start_time.tv_sec) * 1000;
	usec = (cur_time.tv_usec - philosophy->start_time.tv_usec) / 1000;
	elapsed_time = sec + usec;
	if (is_eat_status)
	{
		if (_pthread_mutex_lock(&cur_shared_data->m_last_eat_time) == 1)
			return (-1);
		cur_shared_data->last_eat_time = elapsed_time;
		if (_pthread_mutex_unlock(&cur_shared_data->m_last_eat_time) == 1)
			return (-1);
	}
	return (elapsed_time);
}

int	print_elapse_time(t_philosophy *philosophy,
	const char *status, bool is_eat_status)
{
	const int	identity = philosophy->identity;
	const long	elapsed = get_elapsed_milesecond(philosophy, is_eat_status);

	printf("%ld %d %s\n", elapsed, identity + 1, status);
	return (0);
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (fd < 0)
		return ;
	if (!s)
		return ;
	write(fd, s, strlen(s));
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ')
		++str;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while (*str && ('0' <= *str && *str <= '9'))
	{
		result *= 10;
		result += (*str - '0');
		++str;
	}
	return (sign * result);
}
