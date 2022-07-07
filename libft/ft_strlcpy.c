/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:44:48 by junji             #+#    #+#             */
/*   Updated: 2022/05/25 11:50:54 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	cnt;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	cnt = 1;
	while (*src && ++cnt <= dstsize)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}
//
//#include <stdio.h>
//#include <string.h>
//int main(void)
//{
//	char arr[500];
//	char brr[500];
//
//	printf("%lu %s\n", ft_strlcpy(arr, "hello juna", 50), arr);
//	printf("%ld %s\n", strlcpy(brr, "hello juna", 50), brr);
//
//	memset(arr, 0, 500);
//	memset(brr, 0, 500);
//	printf("%lu %s\n", ft_strlcpy(arr, "hello juna\n", 5), arr);
//	printf("%ld %s\n", strlcpy(brr, "hello juna\n", 5), brr);
//
//	memset(arr, 0, 500);
//	memset(brr, 0, 500);
//	printf("%lu %s\n", ft_strlcpy(arr, "hello juna\n", 0), arr);
//	printf("%ld %s\n", strlcpy(brr, "hello juna\n", 0), brr);
//}
//// src길이가 >= size인 경우 잘림이 발생한다. 이 경우엔 호출자가 책임져야 하는 부분이다.
