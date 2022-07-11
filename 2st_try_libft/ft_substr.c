/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:16:59 by junji             #+#    #+#             */
/*   Updated: 2022/07/11 15:55:33 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty_char(void)
{
	char	*copy;

	copy = malloc(sizeof(char) * 1);
	if (!copy)
		return (0);
	copy[0] = '\0';
	return (copy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*copy;
	size_t	idx;
	size_t	s_length;

	if (!s)
		return (0);
	s_length = ft_strlen(s);
	if (s_length <= start)
		return (empty_char());
	if (s_length - start < len)
		len = s_length - start;
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (0);
	idx = -1;
	while (++idx < len && (start + idx) < s_length)
		copy[idx] = s[start + idx];
	copy[idx] = '\0';
	return (copy);
}
