/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 18:52:24 by junji             #+#    #+#             */
/*   Updated: 2022/05/25 18:55:29 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;
	char		c;

	num = n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num *= -1;
	}
	if (num < 10)
	{
		c = num + '0';
		write(fd, &c, 1);
	}	
	else
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
}
//
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//#include <stdlib.h>
//#include <fcntl.h>
//int main(void)
//{
//	int		fd;
//	char	c;
//	c = 'a';
//	fd = open("1", O_RDWR);
//	ft_putnbr_fd(2147483647, fd);
//	ft_putnbr_fd(0, fd);
//	ft_putnbr_fd(-2147483648, fd);
//	close(fd);
//}
