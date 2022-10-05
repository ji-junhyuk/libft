#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char **argv)
{
//	char *args[] = {"ls", "-al", 0};
//	char *args2[] = {"grep", "-n", "abc", 0};
	char *args3[] = {"grep", "abc", 0};
	char *env[] = { 0 };	/* leave the environment list null */

	printf("About to run /bin/ls\n");
//	execve("/bin/ls", args, env);
	execve("/usr/bin/grep", args3, 0);
	perror("execve");	/* if we get here, execve failed */
	exit(1);
}

