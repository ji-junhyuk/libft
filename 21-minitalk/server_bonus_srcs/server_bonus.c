/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:24:16 by junji             #+#    #+#             */
/*   Updated: 2022/09/27 15:24:57 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"
#include "print_bonus.h"

int	g_byte;

void	recd_one_bit(int signum, siginfo_t *info, void *context)
{	
	(void)context;
	g_byte |= 1;
	usleep(50);
	if (kill(info->si_pid, signum))
		put_error();
}

void	recd_zero_bit(int signum, siginfo_t *info, void *context)
{	
	(void)context;
	usleep(50);
	if (kill(info->si_pid, signum))
		put_error();
}

void	set_sigact(struct sigaction *zero_act, struct sigaction *one_act)
{
	sigemptyset(&(zero_act->sa_mask));
	sigemptyset(&(one_act->sa_mask));
	zero_act->sa_flags = SA_SIGINFO;
	one_act->sa_flags = SA_SIGINFO;
	zero_act->sa_sigaction = recd_zero_bit;
	one_act->sa_sigaction = recd_one_bit;
	sigaction(SIGUSR1, zero_act, 0);
	sigaction(SIGUSR2, one_act, 0);
}

int	main(void)
{
	struct sigaction	zero_act;
	struct sigaction	one_act;
	pid_t				pid;
	int					count;

	set_sigact(&zero_act, &one_act);
	count = 0;
	pid = getpid();
	ft_putnbr(pid);
	while (1)
	{
		pause();
		++count;
		g_byte <<= 1;
		if (count == 8)
		{
			g_byte >>= 1;
			write(1, &g_byte, 1);
			g_byte = 0;
			count = 0;
		}
	}
}
