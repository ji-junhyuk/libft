/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:00:57 by junji             #+#    #+#             */
/*   Updated: 2022/07/09 11:36:59 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		idx;
	char	*last_occurence;

	idx = 0;
	last_occurence = 0;
	while (*s)
	{
		if (*s == (char)c)
			last_occurence = ((char *)s);
		++s;
	}
	if (*s == (char)c)
		return ((char *)s);
	if (last_occurence)
		return (last_occurence);
	return (0);
}
//
//#include <stdio.h>
//#include <ctype.h>
//#include <string.h>
//int main(void)
//{
//	printf(">>>Your<<<\n");
//	printf("%s\n", ft_strrchr("hello0h", 0));
//	printf("%s\n", ft_strrchr("hello0h", 'l'));
//	printf("%s\n", ft_strrchr("hello0h", 'h'));
//	printf("%s\n", ft_strrchr("hello0h", '0'));
//	printf("%s\n", ft_strrchr("hello0h", 'a'));
//	printf(">>>Test<<<\n");
//	printf("%s\n", strrchr("hello0h", 0));
//	printf("%s\n", strrchr("hello0h", 'l'));
//	printf("%s\n", strrchr("hello0h", 'h'));
//	printf("%s\n", strrchr("hello0h", '0'));
//	printf("%s\n", strrchr("hello0h", 'a'));
//}
