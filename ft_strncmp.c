/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:00:23 by junji             #+#    #+#             */
/*   Updated: 2022/07/06 17:28:12 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cnt;

	if (n == 0)
		return (0);
	cnt = 0;
	while (*s1 && (*s1 == *s2) && ++cnt < n)
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
//
//#include <stdio.h>
//#include <stddef.h>
//#include <string.h>
//int main(void)
//{
//	printf(">>>Your<<<\n");
//	printf("%d\n", ft_strncmp("", "", 5));
//	printf("%d\n", ft_strncmp("a", "b", 0));
//	printf("%d\n", ft_strncmp("0", "0", 1));
//	printf("%d\n", ft_strncmp("a", "a", 1));
//	printf("%d\n", ft_strncmp("aba", "aca", 2));
//	printf("%d\n", ft_strncmp("ada", "aca", 2));
//	printf("%d\n", ft_strncmp("abc\222", "abc\0", 5));
//	printf(">>>Test<<<\n");
//	printf("%d\n", strncmp("", "", 5));
//	printf("%d\n", strncmp("a", "b", 0));
//	printf("%d\n", strncmp("0", "0", 1));
//	printf("%d\n", strncmp("a", "a", 1));
//	printf("%d\n", strncmp("aba", "aca", 2));
//	printf("%d\n", strncmp("ada", "aca", 2));
//	printf("%d\n", strncmp("abc\222", "abc\0", 5));
//}
