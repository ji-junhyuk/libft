#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <signal.h>
#include <errno.h>

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int main(void)
{
	unsigned long long flag;
	int byte = 0;
	flag = create_trgb(52, 0xff, 0xff, 0xff);
	printf("flag: %llu\n", flag);
	while (flag > 0)
	{
		if (byte % 8 == 0)
			printf("|");
		if (flag % 2)
			printf("1");
		else
			printf("0");
		flag /= 2;
		++byte;
	}
	return (0);
}
