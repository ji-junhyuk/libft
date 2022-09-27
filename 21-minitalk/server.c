#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int	g_byte; 

void	put_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

void	recd_one_bit(int signum, siginfo_t *info, void *context)
{	
	(void)context;
	g_byte |= 1;
	usleep(30);
	if (kill(info->si_pid, signum) > 0)
		put_error();
}

void	recd_zero_bit(int signum, siginfo_t *info, void *context)
{	
	(void)context;
	usleep(30);
	if (kill(info->si_pid, signum) > 0)
		put_error();
}

typedef struct s_sig_tool
{
	struct sigaction	zero_act;
	struct sigaction	one_act;
	int					count;
	pid_t				pid;
} t_sig_tool;

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

int main(void)
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
