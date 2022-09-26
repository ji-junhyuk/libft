#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	receive(int signum)
{
	(void)signum;
	write(1, "client received...\n", 19);
}

int main(int argc, char *argv[])
{
	struct sigaction zero_act;
	struct sigaction one_act;
	zero_act.sa_handler = receive;
	one_act.sa_handler = receive;

	sigaction(SIGUSR1, &zero_act, 0);
	sigaction(SIGUSR2, &one_act, 0);
	int pid = atoi(argv[1]);

	while (1)
	{
		kill(pid, SIGUSR1);
		pause();
	}
}
