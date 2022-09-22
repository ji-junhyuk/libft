#include <unistd.h>
#include <stdio.h>
int main(void)
{
	pid_t pid;
	pid = getpid();

	printf("%d\n", pid);
	while (1)
	{
		printf("hello");
		sleep(1);
	}
}
