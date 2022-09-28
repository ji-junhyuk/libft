#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>

int	main(void)
{
	int fd[2];
	pipe(fd);
	char buffer[1024];
	pid_t pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1); // 표준 출력을 자식 프로세스의 write file desciptor로 redirect
		close(fd[0]);
		execl("/bin/who", "who", NULL); 
	}
	else
	{
		dup2(fd[0], 0); // 표준 입력을 부모 프로세스의 read file descriptor로 redirect 
		waitpid(pid, NULL, 0);
		close(fd[1]);
		while (read(fd[0], buffer, 1024) != 0)
			;
		printf("The output: \n");
		printf("%s\n", buffer);
	}
}
