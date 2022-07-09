/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:57:59 by junji             #+#    #+#             */
/*   Updated: 2022/05/23 14:16:13 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			idx;
	size_t			cnt;
	unsigned char	*p1;
	unsigned char	*p2;

	if (n == 0)
		return (0);
	idx = 0;
	cnt = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (++cnt < n && p1[idx] == p2[idx])
		++idx;
	return (p1[idx] - p2[idx]);
}
//
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//int main(void)
//{
//	printf(">>>Your<<<\n");
//	printf("%d\n", ft_memcmp("hello", "hella", 5));
//	printf("%d\n", ft_memcmp("hello", "hellz", 5));
//	printf("%d\n", ft_memcmp("hello", "hella", 4));
//	printf("%d\n", ft_memcmp("", "", 0)); 
//	printf("%d\n", ft_memcmp("a", "b", 0)); 
//	printf("%d\n", ft_memcmp("a", "a", 1)); 
//	printf("%d\n", ft_memcmp("aa", "ab", 2)); 
//
//	printf(">>>Test<<<\n");
//	printf("%d\n", memcmp("hello", "hella", 5));
//	printf("%d\n", memcmp("hello", "hellz", 5));
//	printf("%d\n", memcmp("hello", "hella", 4));
//	printf("%d\n", memcmp("", "", 0)); 
//	printf("%d\n", memcmp("a", "b", 0)); 
//	printf("%d\n", memcmp("a", "a", 1)); 
//	printf("%d\n", memcmp("aa", "ab", 2)); 
////	printf("%d\n", memcmp("", "", 8)); // seg
////	printf("%d\n", memcmp("ab", "ab", 8)); // seg
//}
