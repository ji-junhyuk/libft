#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include<stdlib.h>
#include <sys/wait.h>
#include <string.h>
int main(void)
{
	int fd1[2], fd2[2];
	pid_t pid;
	char buf[257], str[257];
	int len, status,i,j;
	if (pipe(fd1) == -1) 
	{
		perror("pipe");
		exit(1);
	}
	if (pipe(fd2) == -1) 
	{
		perror("pipe");
		exit(1);
	} 
	switch (pid = fork()) 
	{
		case -1:
			perror("fork");
			exit(1);
		case 0: //child
			close(fd1[1]);
			close(fd2[0]);
			for(i=1; i<11; i++)
			{ 
				sleep(1);
				str[0]='\0';
				sprintf(str, "Child Process %d\n: ", i);
				write(1, str, 17);
				len=read(fd1[0],buf,256);
				write(1,buf,len);
				buf[0]='\0';
				sprintf(buf,"Good %d\n",i);
				strcat(buf,"\n");
				write(fd2[1],buf,strlen(buf));
				sleep(1);
			} break;
			default:
			close(fd1[0]);
			close(fd2[1]);
			buf[0] = '\0';
			str[0]='\0';
			for(j=1;j<11;j++)
			{ 
				buf[0]='\0';
				sleep(1);
				sprintf(buf, "Hello %d\n",j);
				strcat(buf,"\n");
				write(fd1[1],buf,strlen(buf));
				sleep(1);
				sprintf(str, " Parent Process %d\n",j);
				write(1,str,19);
				len=read(fd2[0],buf,256);
				write(1,buf,len);
			}
			waitpid(pid, &status, 0); 
			break;
	}
	return 0;
}
