/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:05 by junji             #+#    #+#             */
/*   Updated: 2022/07/06 18:26:58 by junji            ###   ########.fr       */
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
//	unsigned char arr[50];
//	unsigned char brr[50];
//	printf(">>>Your<<<\n");
//	memset(arr, 10, 50);
//	for(int idx = 0; idx < 50; ++idx)
//		printf("%d ", (arr[idx]));
//	printf("\n");
//	printf(">>>Test<<<\n");
//	ft_memset(brr, 10, 50);
//	for(int idx = 0; idx < 50; ++idx)
//		printf("%d ", (brr[idx]));
//	printf("\n");
//	int arr5[50];
//	memset(arr5, -1, 200);
//	for(int idx = 0; idx < 50; ++idx)
//		printf("%d ", (arr5[idx]));
//
//	printf("\n");
//	unsigned char test[50];
//	ft_memset(test, 'a', 50);
//	for (int idx = 0; idx < 50; ++idx)
//		printf("%d ", test[idx]);
//}
