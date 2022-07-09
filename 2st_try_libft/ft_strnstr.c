/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:07:56 by junji             #+#    #+#             */
/*   Updated: 2022/07/09 14:07:59 by junji            ###   ########.fr       */
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
