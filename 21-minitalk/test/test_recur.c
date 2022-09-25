#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	recur(unsigned char c)
{
	if (c == 0)
		return ;
	recur(c / 2);
	printf("%d\n", c % 2);
}

int main(int argc, char *argv[])
{
	char a = 97;
	recur(a);
	return (0);
}
