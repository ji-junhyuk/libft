/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:35:20 by junji             #+#    #+#             */
/*   Updated: 2022/09/27 17:00:03 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "print_bonus.h"

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
		usleep(30);
		if (kill(pid, SIGUSR1))
			put_error();
		pause();
	}
}

void	send_bit(int pid, unsigned char c)
{
	if (c == 0)
		return ;
	send_bit(pid, c / 2);
	usleep(50);
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
	pause();
}

void	set_sigact(struct sigaction *zero_act, struct sigaction *one_act)
{
	sigemptyset(&(zero_act->sa_mask));
	sigemptyset(&(one_act->sa_mask));
	zero_act->sa_flags = 0;
	one_act->sa_flags = 0;
	zero_act->sa_handler = receive;
	one_act->sa_handler = receive;
	sigaction(SIGUSR1, zero_act, 0);
	sigaction(SIGUSR2, one_act, 0);
}

int	main(int argc, char *argv[])
{
	int					pid;
	char				*send_message;
	struct sigaction	zero_act;
	struct sigaction	one_act;

	zero_act.sa_handler = receive;
	one_act.sa_handler = receive;
	if (argc != 3)
		put_error();
	pid = ft_atoi(argv[1]);
	send_message = argv[2];
	sigaction(SIGUSR1, &zero_act, 0);
	sigaction(SIGUSR2, &one_act, 0);
	while (*send_message)
	{
		send_padding_bit(pid, *send_message);
		send_bit(pid, *send_message);
		++send_message;
	}
}
