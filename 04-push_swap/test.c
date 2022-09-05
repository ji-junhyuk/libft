#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int	i;

	int num = atoi(argv[1]);
	i = 0;
	while (++i <= num)
	{
		printf("%d ", i);
	}
	printf("\n\n");
	while (--i > 0)
	{
		printf("%d ", i);
	}
	printf("\n\n");
	return 0;
}
