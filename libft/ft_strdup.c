/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 00:33:50 by junji             #+#    #+#             */
/*   Updated: 2022/06/01 19:37:16 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcpy(char *dest, const char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

char	*ft_strdup(const char *src)
{
	size_t	src_len;
	char	*copy;

	src_len = ft_strlen(src);
	copy = malloc(sizeof(char) * (src_len + 1));
	if (!copy)
		return (0);
	ft_strcpy(copy, src);
	return (copy);
}
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//#include <stdlib.h>
//int main(void)
//{
//	char *arr;
//	char *arr2;
//	printf(">>>Your<<<\n");
//	printf("%s\n", arr = ft_strdup("hello, piscine~!"));
//	
//	printf(">>>Test<<<\n");
//	printf("%s\n", arr2 = strdup("hello, piscine~!"));
//	
//}
