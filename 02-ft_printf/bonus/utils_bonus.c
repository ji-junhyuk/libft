#include "printf_bonus.h"

int	ft_puthex_fd_2(unsigned int value, int fd, t_tool *tool)
{
	const char	*hex = "0123456789ABCDEF";

	if (value < 16)
	{
		if (write(1, &hex[value], 1) == -1)
			return (-1);
		++tool->printed;
	}	
	else
	{
		ft_puthex_fd_2(value / 16, fd, tool);
		ft_puthex_fd_2(value % 16, fd, tool);
	}
	return (0);
}

int	ft_puthex_fd(unsigned int value, int fd, t_tool *tool)
{
	const char	*hex = "0123456789abcdef";

	if (value < 16)
	{
		if (write(1, &hex[value], 1) == -1)
			return (-1);
		++tool->printed;
	}	
	else
	{
		ft_puthex_fd(value / 16, fd, tool);
		ft_puthex_fd(value % 16, fd, tool);
	}
	return (0);
}

int	ft_putnbr_fd(long num, int fd, t_tool *tool)
{
	char	c;

	if (num < 10)
	{
		c = num + '0';
		if (write(fd, &c, 1) == -1)
			return (-1);
		++tool->printed;
	}	
	else
	{
		ft_putnbr_fd(num / 10, fd, tool);
		ft_putnbr_fd(num % 10, fd, tool);
	}
	return (0);
}

int	find_len_hex(long num)
{
	int	len;

	len = 0;
	while (1)
	{
		++len;
		num /= 16;
		if (num == 0)
			return (len);
	}
}

int	find_len(long num)
{
	int	len;

	len = 0;
	while (1)
	{
		++len;
		num /= 10;
		if (num == 0)
			return (len);
	}
}

