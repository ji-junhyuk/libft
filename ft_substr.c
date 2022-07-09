/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:19:11 by junji             #+#    #+#             */
/*   Updated: 2022/07/09 12:37:18 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*copy;
	size_t	idx;

	if (!s)
		return (0);
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	if (ft_strlen(s) <= start)
	{
		copy = malloc(sizeof(char) * 1);
		if (!copy)
			return (0);
		copy[0] = '\0';
		return (copy);
	}
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (0);
	idx = -1;
	while (++idx < len && (start + idx) < ft_strlen(s))
		copy[idx] = s[start + idx];
	copy[idx] = '\0';
	return (copy);
}
//
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//#include <stdlib.h>
//int main(void)
//{
//	char *p;
//
//	p = ft_substr("hello, junto", 0, 5);
//	printf("%s\n", p);
//
//	free(p);
//	p = NULL;	
//	p = ft_substr("hello", 0, 42000);
//	printf("%s\n", p);
//
//	free(p);
//	p = NULL;
//	p = ft_substr("hello", 5, 5);
//	printf("%s\n", p);
//
//	free(p);
//	p = NULL;
//	p = ft_substr("hello", 3, 5);
//	printf("%s\n", p);
//
//	free(p);
//	p = NULL;	
//	p = ft_substr("hello", 1, 1);
//	printf("%s\n", p);
//
//	free(p);
//	p = NULL;	
////	p = ft_substr("hello world", 6, 42);
////	p = ft_substr("hello world", 42, 6);
//	printf("%s\n", p);
//}
