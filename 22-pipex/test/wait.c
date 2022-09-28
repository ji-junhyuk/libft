#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

void MakeChild(int seq,int rval);
int main()
{
    srand((unsigned)time(0));

    int i = 0;
    for(i=0; i<5; i++)
    {
        MakeChild(i+1, rand()%10);
    }

    int rval=0;
    pid_t cpid=0;
    while(i>0)
    {
        cpid = wait(&rval);
        printf("cpid:%d exit status:%#x\n",cpid, rval);
        i--;
    }
    return 0;
}
void MakeChild(int seq,int rval)
{
    pid_t cpid = fork();

    if(cpid == -1)
    {
        perror("error fork");
        return;
    }

    if(cpid>0)
    {
        printf("fork child pid:%u\n",cpid);
    }
    else
    {
        printf("pid:%d sleep %dseconds\n",getpid(), rval);
        sleep(rval);
	}
}
