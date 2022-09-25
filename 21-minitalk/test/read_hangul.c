#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *str = "가";
	char	a, b, c;
	a = *str;
	write(1, str++, 1);
	b = *str;
	write(1, str++, 1);
	c = *str;
	write(1, str, 1);
	printf("%d\n", a);
	printf("%d\n", b);
	printf("%d\n", c);

	a = -22;
	b = -80;
	c = -128;
	write(1, &a, 1);
	write(1, &b, 1);
	write(1, &c, 1);

	int f = 234;
	write(1, &f, 1);
	f = 176;
	write(1, &f, 1);
	f = 128;
	write(1, &f, 1);
	char d;
	d = 0b11101010;
	write(1, &d, 1);
	d = 0b10110000;
	write(1, &d, 1);
	d = 0b10000000;
	write(1, &d, 1);
	

//	while (1)
//	{
//
//	}
	return (0);
}
