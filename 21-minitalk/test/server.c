#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#define sec 250

int byte, count; 

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
	byte |= 1;
	if (count != 7)
		byte = byte << 1;
	count += 1;
	if (count == 8)
	{
		write(1, &byte, 1);
		byte = 0;
		count = 0;
	}
	//usleep(sec);
	if (kill(info->si_pid, signum) > 0)
		put_error();
	pause();
}

void	recd_zero_bit(int signum, siginfo_t *info, void *context)
{	
	(void)context;
	if (count != 7)
		byte = byte << 1;
	count += 1;
	if (count == 8)
	{
		write(1, &byte, 1);
		byte = 0;
		count = 0;
	}
	//usleep(sec);
	if (kill(info->si_pid, signum) > 0)
		put_error();
	pause();
}

int main(void)
{
	pid_t pid;
	pid = getpid();
	struct sigaction zero_act;
	struct sigaction one_act;

	zero_act.sa_flags = SA_SIGINFO;
	zero_act.sa_sigaction = recd_zero_bit;
	one_act.sa_flags = SA_SIGINFO;
	one_act.sa_sigaction = recd_one_bit;
	sigaction(SIGUSR1, &zero_act, 0);
	sigaction(SIGUSR2, &one_act, 0);
	ft_putnbr(pid);
	while (1)
	{
		;
	}
}
