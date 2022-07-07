/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 19:49:59 by junji             #+#    #+#             */
/*   Updated: 2022/05/26 14:49:51 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	cnt;

	cnt = -1;
	if (!(*needle))
		return ((char *)(haystack));
	if (!(*haystack) || !len)
		return (0);
	if (ft_strlen(needle) > len)
		return (0);
	while (*haystack && ++cnt <= len - ft_strlen(needle))
	{
		if (*haystack == *needle)
		{
			if (ft_strncmp((char *)haystack,
					(char *)needle, ft_strlen(needle)) == 0)
				return ((char *)(haystack));
		}
		++haystack;
	}
	return (0);
}
//
//#include <string.h>
//#include <stdio.h>
//int	main(void)
//{
//	printf(">>>>YOURS<<<<\n");
//	printf("%s\n", ft_strnstr("", "", 3));
//	printf("%s\n", ft_strnstr("abc", "", 1));
//	printf("%s\n", ft_strnstr("abc", "aaa", 3));
//	printf("%s\n", ft_strnstr("abc", "", 3));
//	printf("%s\n", ft_strnstr("", "abc", 3));
//	printf("%s\n", ft_strnstr("abc", "abc", 3));
//	printf("%s\n", ft_strnstr("aabcbds", "bc", 2));
//	printf("%s\n", ft_strnstr("aabcbds", "zxc", 3));
//	printf("%s\n", ft_strnstr("sdabgdabc", "abc", 2));
//
//	printf("%s\n", ft_strnstr("abcsdabgdabc", "abc", 2));
//	printf("%s\n", ft_strnstr("abcsdabgdabc", "abc", 2));
//
//	printf("%s\n", ft_strnstr("abcsdabgdabc", "ab", 2));
//	printf("%s\n", ft_strnstr("sdgabcsdabgdabc", "ab", 2));
//	printf("%s\n", ft_strnstr("hello nice~ junto very good", "lorem", 15));
//	printf("%s\n", ft_strnstr("hello nice~ junto well done", "junto", 15));
//
//	printf(">>>>TESTER<<<<\n");
//	printf("%s\n", strnstr("", "", 3));
//	printf("%s\n", strnstr("abc", "", 1));
//	printf("%s\n", strnstr("abc", "aaa", 3));
//	printf("%s\n", strnstr("abc", "", 3));
//	printf("%s\n", strnstr("", "abc", 3));
//	printf("%s\n", strnstr("abc", "abc", 3));
//	printf("%s\n", strnstr("aabcbds", "bc", 3));
//	printf("%s\n", strnstr("aabcbds", "zxc", 3));
//	printf("%s\n", strnstr("sdabgdabc", "abc", 2));
//
//	printf("%s\n", strnstr("abcsdabgdabc", "abc", 2));
//	printf("%s\n", strnstr("abcsdabgdabc", "abc", 2));
//
//	printf("%s\n", strnstr("abcsdabgdabc", "ab", 2));
//	printf("%s\n", strnstr("sdgabcsdabgdabc", "ab", 2));
//	printf("%s\n", strnstr("hello nice~ junto very good", "lorem", 15));
//	printf("%s\n", strnstr("hello nice~ junto well done", "junto", 15));
//}
