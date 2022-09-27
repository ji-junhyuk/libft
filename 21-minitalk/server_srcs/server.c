#include "server.h"
#include "print.h"

int	g_byte; 

void	recd_one_bit(int signum)
{	
	g_byte |= 1;
//	usleep(10);
}

void	recd_zero_bit(int signum)
{	
//	usleep(10);
}

void	set_sigact(struct sigaction *zero_act, struct sigaction *one_act)
{
	sigemptyset(&(zero_act->sa_mask));
	sigemptyset(&(one_act->sa_mask));
	zero_act->sa_flags = 0;
	one_act->sa_flags = 0;
	zero_act->sa_handler = recd_zero_bit;
	one_act->sa_handler = recd_one_bit;
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
