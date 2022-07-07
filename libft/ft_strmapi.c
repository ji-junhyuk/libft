/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:06:37 by junji             #+#    #+#             */
/*   Updated: 2022/05/26 19:28:03 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*copy;
	unsigned int	len;
	unsigned int	idx;

	if (!s)
		return (0);
	len = ft_strlen(s);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (0);
	idx = -1;
	while (++idx < len)
		copy[idx] = f(idx, s[idx]);
	copy[idx] = '\0';
	return (copy);
}
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//#include <stdlib.h>
//
//char func(unsigned int idx, char c)
//{
//	return (c + idx);
//}
//
//int main()
//{
//	char	*str = "abcdefgh";
//	char	*str2;
//	str2 = ft_strmapi(str, func);
//	printf("%s\n", str2);
//}
