#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <signal.h>
#include <errno.h>

int main(void)
{
	char *args[] = {"ls", "-al", 0};
	for (int idx = 0; idx < 4; ++idx)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			printf("hello child\n");
			execve("/bin/ls", args, 0);
		}
	}
	return (0);
}
