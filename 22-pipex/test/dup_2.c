#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

int	main(void)
{
	int newfd1, newfd2, length;
	char buf[1000];

	memset(buf, 0, 1000);

	newfd1 = dup(0);
	newfd2 = dup(1);

	printf("newfd1:%d, newfd2:%d\n", newfd1, newfd2);

	length = read(newfd1, buf, 1000);
	write(newfd2, buf, length);
}
