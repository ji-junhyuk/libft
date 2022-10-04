#include <stdio.h>
#include <unistd.h>

int main(void)
{
	if (access("/bin/ls", F_OK) == 0)
	{
		printf("hello\n");
	}
}
