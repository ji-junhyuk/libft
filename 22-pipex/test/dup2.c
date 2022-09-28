#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

int	main(void)
{
	int fd[2];
	char buf[1000];
	pipe(fd);

	memset(buf, 0, 1000);

	if (fork() == 0)
	{
		close(fd[0]);
		strcpy(buf, "hello, junto");
		dup2(fd[1], 1);
		printf("%s\n", buf);
		exit(0);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		dup2(fd[0], 0);
		scanf("%[^\n]", buf);
		printf("%s (prints in parent)\n", buf);
	}
	return (0);
}
