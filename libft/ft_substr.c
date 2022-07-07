/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 10:19:11 by junji             #+#    #+#             */
/*   Updated: 2022/05/25 10:53:36 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*copy;
	size_t	idx;

	if (!s)
		return (0);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (0);
	if (ft_strlen(s) <= start)
	{
		copy[0] = '\0';
		return (copy);
	}
	idx = -1;
	while (++idx < len)
		copy[idx] = s[start++];
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
//}
