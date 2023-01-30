/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:20:23 by junji             #+#    #+#             */
/*   Updated: 2023/01/30 09:01:00 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	msleep(long time)
{
	struct timeval	cur_time;
	long			start_sec;
	int				start_usec;
	long			waiting_time;

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

long	get_elapsed_milesecond(t_philosophy *philo, bool is_eat_status)
{
	struct timeval	cur_time;
	long			elapsed_time;
	long			sec;
	int				usec;
	t_shared_data	*s;

	gettimeofday(&cur_time, NULL);
	s = philo->shared_data;
	sec = (cur_time.tv_sec - philo->start_time.tv_sec) * 1000;
	usec = (cur_time.tv_usec - philo->start_time.tv_usec) / 1000;
	elapsed_time = sec + usec;
	if (is_eat_status)
	{
		if (_pthread_mutex_lock(&s->m_last_eat_time[philo->identity]) == 1)
			return (-1);
		s->last_eat_time[philo->identity] = elapsed_time;
		if (_pthread_mutex_unlock(&s->m_last_eat_time[philo->identity]) == 1)
			return (-1);
	}
	return (elapsed_time);
}

int	print_elapse_time(t_philosophy *philo,
	const char *status, bool is_eat_status)
{
	const int		i = philo->identity;
	const long		elapsed = get_elapsed_milesecond(philo, is_eat_status);
	t_shared_data	*shared_data;

	shared_data = philo->shared_data;
	if (_pthread_mutex_lock(&shared_data->m_print[i]) == 1)
		return (-1);
	if (shared_data->is_print_possible[i])
		printf("\033[0;32m%06ld \033[0;37m%03d %s\n", elapsed, i + 1, status);
	if (_pthread_mutex_unlock(&shared_data->m_print[i]) == 1)
		return (-1);
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
