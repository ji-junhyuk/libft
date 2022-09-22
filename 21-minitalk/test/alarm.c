#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void	handler(int signo)
{
	psignal(signo, "Received Signal");
}

int	main(void)
{
	signal(SIGALRM, handler);

	alarm(2);
	printf("Wait...\n");
	sleep(3);
	
	return (0);
}
