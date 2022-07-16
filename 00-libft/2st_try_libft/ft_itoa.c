/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:29:45 by junji             #+#    #+#             */
/*   Updated: 2022/07/09 16:55:30 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_len(long long num)
{
	int	len;

	len = 0;
	if (num < 0)
	{
		++len;
		num *= -1;
	}
	while (1)
	{
		++len;
		num /= 10;
		if (num == 0)
			return (len);
	}
}

char	*ft_itoa(int n)
{
	char		*copy;
	long long	num;
	int			len;

	num = n;
	len = find_len(num);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (0);
	copy[len] = '\0';
	if (num < 0)
	{
		copy[0] = '-';
		num *= -1;
	}
	while (1)
	{
		copy[--len] = num % 10 + '0';
		num /= 10;
		if (num == 0)
			break ;
	}
	return (copy);
}
