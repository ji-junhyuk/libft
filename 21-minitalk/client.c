#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	int pid;
	(void)argc;
	(void)argv;
	
	pid = atoi(argv[1]);
	kill(pid, SIGUSR1);
}
