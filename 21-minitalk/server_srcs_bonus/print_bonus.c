/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:34:52 by junji             #+#    #+#             */
/*   Updated: 2022/09/27 15:23:20 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_bonus.h"

void	put_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

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
