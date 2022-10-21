#include <stdlib.h>
#include <stdio.h>

void	put_error(char *str)
{
	perror(str);
	exit(1);
}
