#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <signal.h>
#include <errno.h>

//int	create_trgb(unsigned int t, unsigned int r, unsigned int g, unsigned int b)
int	create_trgb( int t,  int r,  int g,  int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int main(void)
{
//	unsigned long long flag;

	unsigned int flag;
	int byte = 0;
	flag = create_trgb(255, 255, 255 , 255);
	printf("flag: %u\n", flag);
	while (flag != 0)
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
