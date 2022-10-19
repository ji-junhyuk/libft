#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <signal.h>
#include <errno.h>

int create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){t, r, g, b});
}

int main(void)
{
	unsigned int flag;
	char rgb[4];
	for (int idx = 0; idx < 4; ++idx)
		rgb[idx] = 0xff;
	flag = create_trgb(rgb[0], rgb[1], rgb[2], rgb[3]);
	printf("flag:%u\n", flag);
	return (0);
}
