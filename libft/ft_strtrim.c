/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 11:23:03 by junji             #+#    #+#             */
/*   Updated: 2022/05/27 01:19:56 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		size;
	char		*copy;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		++s1;
	size = ft_strlen(s1);
	while (size > 0 && ft_strchr(set, s1[size - 1]))
		--size;
	copy = ft_substr(s1, 0, size);
	return (copy);
}
//
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//#include <stdlib.h>
//int main(void)
//{
//	printf("%s\n", ft_strtrim("hello", "ho"));
//}
