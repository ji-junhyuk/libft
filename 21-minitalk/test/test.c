#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void	recd_one_bit(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	write(1, "server received...\n", 19);

	kill(info->si_pid, signum);
}

int main(void)
{
	int pid = getpid();
	printf("%d\n", pid);
	struct sigaction zero_act;
	zero_act.sa_sigaction = recd_one_bit;
	sigaction(SIGUSR1, &zero_act, 0);
	while (1)
	{
		write(1, "a", 1);
		pause();
	}
}
