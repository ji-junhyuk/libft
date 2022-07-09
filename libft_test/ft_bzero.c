/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:41:23 by junji             #+#    #+#             */
/*   Updated: 2022/07/06 17:42:52 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
//
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//int main(void)
//{
//	unsigned char arr[50];
//	printf(">>>Your<<<\n");
//	memset(arr, 2, 50);
//	ft_bzero(arr, 50);
//	for(int idx = 0; idx < 50; ++idx)
//		printf("%d ", (arr[idx]));
//	printf("\n");
//
//	unsigned char str[100] = "hello, jun\n";
//	ft_bzero(str, 100);
//	for(int idx = 0; idx < 100; ++idx)
//		printf("%d ", (str[idx]));
//	printf("\n");
//
//
//	printf(">>>Test<<<\n");
//	memset(arr, 2, 50);
//	bzero(arr, 50);
//	for(int idx = 0; idx < 50; ++idx)
//		printf("%d ", (arr[idx]));
//	printf("\n");
//	unsigned char str2[100] = "hello, jun\n";
//	ft_bzero(str2, 100);
//	for(int idx = 0; idx < 100; ++idx)
//		printf("%d ", (str[idx]));
//	printf("\n");
//}
////void	ft_bzero(void	*s, size_t n)
////{
////	size_t idx;
////
////	if (n == 0)
////		return ;
////	unsigned char	*p;
////	p = (unsigned char *)s;
////	idx = -1;
////	while (++idx < n)
////		p[idx] = 0;
////}
