/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:10:54 by junji             #+#    #+#             */
/*   Updated: 2022/07/06 12:22:18 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (0);
}
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//int main(void)
//{
//	printf(">>>Your<<<\n");
//	printf("%s\n", ft_strchr("", 0));
//	printf("%s\n", ft_strchr("hello0", 0));
//	printf("%s\n", ft_strchr("hello0", 'l'));
//	printf("%s\n", ft_strchr("hello0h", 'h'));
//	printf("%s\n", ft_strchr("hello0h", '0'));
//	printf("%s\n", ft_strchr("hello0h", '\0'));
//	printf("%s\n", ft_strchr("hello0h", 's'));
//	printf(">>>Test<<<\n");
//	printf("%s\n", strchr("", 0));
//	printf("%s\n", strchr("hello0", 0));
//	printf("%s\n", strchr("hello0", 'l'));
//	printf("%s\n", strchr("hello0h", 'h'));
//	printf("%s\n", strchr("hello0h", '0'));
//	printf("%s\n", strchr("hello0h", '\0'));
//	printf("%s\n", strchr("hello0h", 's'));
//}
