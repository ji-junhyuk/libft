/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:59:00 by junji             #+#    #+#             */
/*   Updated: 2022/10/13 17:02:02 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_utils2_bonus.h"
#include "string_utils_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*copy;
	size_t	s1_size;
	size_t	s2_size;
	size_t	size;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	size = s1_size + s2_size;
	copy = malloc(sizeof(char) * (size + 1));
	if (!copy)
	{
		free(s1);
		s1 = 0;
		return (0);
	}
	while (*s1)
		*copy++ = *s1++;
	s1 -= s1_size;
	free(s1);
	while (*s2)
		*copy++ = *s2++;
	*copy = '\0';
	copy -= (size);
	return (copy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*copy;
	size_t	idx;

	if (!len)
		return (0);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (0);
	idx = -1;
	while (++idx < len)
		copy[idx] = s[start++];
	copy[idx] = '\0';
	return (copy);
}
