#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	ft_putnbr(int n)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}
int main(int argc, char *argv[])
{
	ft_putnbr(atoi(argv[1]));

	return (0);
}
