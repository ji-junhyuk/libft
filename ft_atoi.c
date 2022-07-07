/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:52:02 by junji             #+#    #+#             */
/*   Updated: 2022/07/06 18:02:40 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_space(char c)
{
	if (c >= 9 && c <= 13)
		return (1);
	if (c == 32)
		return (1);
	return (0);
}

int	is_sign(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (is_space(*str))
		++str;
	if (*str && is_sign(*str))
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while (*str && is_num(*str))
	{
		result *= 10;
		result += (*str - '0');
		++str;
	}
	return (sign * result);
}
//
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//#include <stdlib.h>
//int	main(void)
//{
//	printf(">>>Your<<<\n");
//	printf("%d\n", ft_atoi(""));
//	printf("%d\n", ft_atoi("   ---+--+1234ab567"));
//	printf("%d\n", ft_atoi(" \n \t \v  -12345678ab567+"));
//	printf("%d\n", ft_atoi(" \n \t \v  -+12345678ab567+"));
//	printf("%d\n", ft_atoi(" \n \t \v  +12345678ab567+"));
//	printf("%d\n", ft_atoi(" \n \t \v  12345678ab567+"));
//	printf("%d\n", ft_atoi(" \n \t \v  -2147483648+"));
//	printf("%d\n", ft_atoi(" \n \t \v  2147483647+"));
//	printf("%d\n", ft_atoi("99999999999999999999999999"));
//	printf("%d\n", ft_atoi("2222222222222222222222"));
//	printf("%d\n", ft_atoi("-99999999999999999999999999"));
//	printf("%d\n", ft_atoi("-2222222222222222222222"));
//	printf(">>>Test<<<\n");
//	printf("%d\n", atoi(""));
//	printf("%d\n", atoi("   ---+--+1234ab567"));
//	printf("%d\n", atoi(" \n \t \v  -12345678ab567+"));
//	printf("%d\n", atoi(" \n \t \v  -+12345678ab567+"));
//	printf("%d\n", atoi(" \n \t \v  +12345678ab567+"));
//	printf("%d\n", atoi(" \n \t \v  12345678ab567+"));
//	printf("%d\n", atoi(" \n \t \v  -2147483648+"));
//	printf("%d\n", atoi(" \n \t \v  2147483647+"));
//	printf("%d\n", atoi("99999999999999999999999999"));
//	printf("%d\n", atoi("2222222222222222222222"));
//	printf("%d\n", atoi("-9999999999999999999999999999999999999999999999999999"));
//	printf("%d\n", atoi("-2147483649000000000000"));
//}
