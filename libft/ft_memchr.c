/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:07:39 by junji             #+#    #+#             */
/*   Updated: 2022/07/06 18:11:46 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			idx;
	unsigned char	*p;

	p = (unsigned char *)s;

	idx = -1;
	while (++idx < n)
	{
		if (p[idx] == (unsigned char)c)
			return ((void *)&p[idx]);
	}
	return (0);
}
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//int main(void)
//{
//	printf(">>>Your<<<\n");
//	printf("%s\n", (char *)ft_memchr("hello", 'l', 2));
//	printf("%s\n", (char *)ft_memchr("hello", 'o', 2));
//	printf("%s\n", (char *)ft_memchr("hello", 'h', 0));
//	printf("%s\n", (char *)ft_memchr("hello", 'o', 5));
//	printf("%s\n", (char *)ft_memchr("hello", 'h', 1));
////	printf("%s\n", (char *)ft_memchr("hello", 'a', 8));
//	
//	printf(">>>Test<<<\n");
//	printf("%s\n", (char *)memchr("hello", 'l', 2));
//	printf("%s\n", (char *)memchr("hello", 'o', 2));
//	printf("%s\n", (char *)memchr("hello", 'h', 0));
//	printf("%s\n", (char *)memchr("hello", 'o', 5));
//	printf("%s\n", (char *)memchr("hello", 'h', 1));
////	printf("%s\n", (char *)memchr("hello", 'a', 8)); // seg
//}
