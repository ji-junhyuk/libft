/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:07:56 by junji             #+#    #+#             */
/*   Updated: 2022/07/11 15:37:54 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	cnt;
	size_t	needle_len;

	cnt = -1;
	if (!(*needle))
		return ((char *)(haystack));
	if (!(*haystack) || !len)
		return (0);
	if (ft_strlen(needle) > len)
		return (0);
	needle_len = ft_strlen(needle);
	while (*haystack && ++cnt <= len - needle_len)
	{
		if (*haystack == *needle)
		{
			if (ft_strncmp((char *)haystack,
					(char *)needle, needle_len) == 0)
				return ((char *)(haystack));
		}
		++haystack;
	}
	return (0);
}
