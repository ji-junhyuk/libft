/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:16:32 by junji             #+#    #+#             */
/*   Updated: 2022/05/26 18:30:23 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*s1;
	const unsigned char	*s2;
	size_t				idx;

	s1 = dst;
	s2 = src;
	if (dst == src || len == 0)
		return (dst);
	if (s1 <= s2)
	{
		idx = -1;
		while (++idx < len)
			s1[idx] = s2[idx];
	}
	else
	{
		while (len-- > 0)
			s1[len] = s2[len];
	}
	return (dst);
}
//
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//int main(void)
//{
//	printf(">>>Your<<<\n");
//	char str[500];
//	strcpy(str, "test");
//	ft_memmove(str, str + 2, 4);
//	printf("%s\n", str);
//	strcpy(str, "testaaa");
//	ft_memmove(str + 2, str, 5);
//	printf("%s\n", str);
//	strcpy(str, "test");
//	ft_memmove(str, str, 4);
//	printf("%s\n", str);
//	strcpy(str, "junto");
//	ft_memmove(str, str, 0);
//	printf("%s\n", str);
//
//	printf(">>>Test<<<\n");
//	strcpy(str, "test");
//	memmove(str, str + 2, 4);
//	printf("%s\n", str);
//	strcpy(str, "testaaa");
//	memmove(str + 2, str, 5);
//	printf("%s\n", str);
//	strcpy(str, "test");
//	memmove(str, str, 4);
//	printf("%s\n", str);
//	strcpy(str, "junto");
//	memmove(str, str, 0);
//	printf("%s\n", str);
//}
