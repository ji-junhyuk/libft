/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:05 by junji             #+#    #+#             */
/*   Updated: 2022/07/09 10:11:18 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	size_t			idx;

	idx = -1;
	p = (unsigned char *)b;
	while (++idx < len)
		p[idx] = c;
	return (b);
}
//
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//int main(void)
//{
//	int arr[50];
//	int brr[50];
//	printf(">>>Your<<\n");
//	ft_memset(arr, 1, 50);
//	for(int idx = 0; idx < 50; ++idx)
//		printf("%d ", (arr[idx]));
//	printf("\n\n");
//
//	printf(">>>Test<<<\n");
//	memset(brr, 1, 50);
//	for(int idx = 0; idx < 50; ++idx)
//		printf("%d ", (brr[idx]));
//	printf("\n\n");
//
//	int arr2[50];
//	memset(arr2, -1, 200);
//	for(int idx = 0; idx < 50; ++idx)
//		printf("%d ", (arr2[idx]));
//	printf("\n\n");
//
//	memset(arr2, -1, 200);
//	for(int idx = 0; idx < 50; ++idx)
//		printf("%d ", (arr2[idx]));
//	printf("\n\n");
//
//	int brr2[50];
//	memset(brr2, 5, 200);
//	for(int idx = 0; idx < 50; ++idx)
//		printf("%d ", (brr2[idx]));
//	printf("\n\n");
//}
