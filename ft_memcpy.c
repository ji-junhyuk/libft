/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:31:47 by junji             #+#    #+#             */
/*   Updated: 2022/05/27 00:37:42 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			idx;
	unsigned char	*p1;
	unsigned char	*p2;

	if (dst == src)
		return (dst);
	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	idx = -1;
	while (++idx < n)
		p1[idx] = p2[idx];
	return (dst);
}
//
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//int main(void)
//{
//	char arr[500];
//	printf(">>>Your<<<\n");
//	strcpy(arr, "hello");
//	memcpy(arr, "abc", 4);
//	printf("%s\n", arr);
//	strcpy(arr, "hello");
//	memcpy(arr, "abc", 3);
//	printf("%s\n", arr);
//
////	strcpy(arr, "");
////	ft_memcpy(arr, "", 3);
////	printf("%s\n", arr);
//
//	printf(">>>Test<<<\n");
//	strcpy(arr, "hello");
//	memcpy(arr, "abc", 4);
//	printf("%s\n", arr);
//	strcpy(arr, "hello");
//	memcpy(arr, "abc", 3);
//	printf("%s\n", arr);
//
////	strcpy(arr, "");
////	memcpy(arr, "", 0);
////	printf("%s\n", arr);	
//}
