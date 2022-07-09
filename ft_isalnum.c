/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 16:42:58 by junji             #+#    #+#             */
/*   Updated: 2022/07/08 15:47:57 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
//
//#include <stdio.h>
//#include <ctype.h>
//
//int main(void)
//{
//	printf(">>>Your<<<\n");
//	printf("%d\n", ft_isalnum(0));
//	printf("%d\n", ft_isalnum(1));
//	printf("%d\n", ft_isalnum(2));
//	printf("%d\n", ft_isalnum('2'));
//	printf("%d\n", ft_isalnum('a'));
//	printf("%d\n", ft_isalnum('A'));
//	printf(">>>Test<<<\n");
//	printf("%d\n", isalnum(0));
//	printf("%d\n", isalnum(1));
//	printf("%d\n", isalnum(2));
//	printf("%d\n", isalnum('2'));
//	printf("%d\n", isalnum('a'));
//	printf("%d\n", isalnum('A'));
//}
