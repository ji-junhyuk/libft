/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:20:37 by junji             #+#    #+#             */
/*   Updated: 2022/09/27 15:21:08 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "print.h"

int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		result *= 10;
		result += (*str - '0');
		++str;
	}
	return (result);
}

void	send_padding_bit(int pid, unsigned char c)
{
	int	len;

	len = 0;
	while (c > 0)
	{
		++len;
		c /= 2;
	}
	len = 8 - len;
	while (--len >= 0)
	{
		if (kill(pid, SIGUSR1))
			put_error();
		usleep(30);
	}
}

void	send_bit(int pid, unsigned char c)
{
	if (c == 0)
		return ;
	send_bit(pid, c / 2);
	if (c % 2)
	{
		if (kill(pid, SIGUSR2))
			put_error();
	}
	else
	{
		if (kill(pid, SIGUSR1))
			put_error();
	}
	usleep(50);
}

int	main(int argc, char *argv[])
{
	int		pid;
	char	*send_message;

	if (argc != 3)
		put_error();
	pid = ft_atoi(argv[1]);
	send_message = argv[2];
	while (*send_message)
	{
		send_padding_bit(pid, *send_message);
		send_bit(pid, *send_message);
		++send_message;
	}
}
