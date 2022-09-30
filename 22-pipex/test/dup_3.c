#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>

int main() {
        int fd[2], n = 0;
        pipe(fd); /* fd[0] : for reading, fd[1] : for writing */
        pid_t pid = fork();
        if (pid == 0) 
		{ // for client
                close(STDOUT_FILENO);
                dup(fd[1]);  // 표준출력을 자식 프로세스의 write file descriptor 로 redirect 시킴.
							 // dup(fd[1])은 표준입력으로..
                close(fd[0]); // 필요 없는 file descriptor 을 닫음.
                printf("%d\n",100);
        } else { //for server
                close(STDIN_FILENO);
                dup(fd[0]); // 표준입력을 부모프로세스의 read file descriptor 로 redirect 시킴.
							// 표준입력을 닫고, fd[0]:reading을 위한 것을 표준입력으로 열어둠.
                waitpid(pid,NULL,0);
                close(fd[1]);  // 필요 없는 file descriptor 을 닫음.
                scanf("%d",&n);
                printf("input value from child process is %d\n",n);
        }
}
