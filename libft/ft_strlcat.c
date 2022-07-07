/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:47:43 by junji             #+#    #+#             */
/*   Updated: 2022/05/26 20:45:12 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	cnt;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dest_len >= dstsize)
		return (dstsize + src_len);
	cnt = 0;
	while (*dst)
	{
		++cnt;
		++dst;
	}
	while (*src && ++cnt < dstsize)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len + dest_len);
}
//
//#include <stdio.h>
//#include <string.h>
//int	main(void)
//{
//	char arr[500];
//	char brr[500];
//	strcpy(arr, "yoyo");
//	printf(">>>>YOURS<<<<\n");
//	printf("1. %lu\n", ft_strlcat(arr, "hello, piscine", 19));
//	printf("1. %s\n", arr);
//
//	memset(arr, 0, 500);
//	strcpy(arr, "yoyo");
//	//사이즈가 18,  잘림이 발생한다
//	printf("2. %lu\n", ft_strlcat(arr, "hello, piscine", 13));
//	printf("2. %s\n", arr);
//
//	memset(brr, 0, 500);
//	strcpy(brr, "yoyo");
//	//dest size가 size보다 작은 경우
//	printf("3. %lu\n", ft_strlcat(brr, "hello, piscine", 3)); 
//	printf("3. %s\n", brr);
//
//	strcpy(brr, "yoyo");
//	printf(">>>>TESTER<<<<\n");
//	printf("1. %lu\n", strlcat(brr, "hello, piscine", 19));
//	printf("1. %s\n", brr);
//
//	memset(brr, 0, 500);
//	strcpy(brr, "yoyo");
//	//사이즈가 18,  잘림이 발생한다.
//	printf("2. %lu\n", strlcat(brr, "hello, piscine", 13)); 
//	printf("2. %s\n", brr);
//
//	memset(brr, 0, 500);
//	strcpy(brr, "yoyo");
//	//dest size가 size보다 작은 경우
//	printf("3. %lu\n", strlcat(brr, "hello, piscine", 3)); 
//	printf("3. %s\n", brr);
//}
