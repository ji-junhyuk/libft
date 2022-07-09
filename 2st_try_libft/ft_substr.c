/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:16:59 by junji             #+#    #+#             */
/*   Updated: 2022/07/09 16:57:55 by junji            ###   ########.fr       */
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

	if (!s)
		return (0);
	if (ft_strlen(s) <= start)
		return (empty_char());
	if (ft_strlen(s) - start < len)
		len = ft_strlen(s) - start;
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (0);
	idx = -1;
	while (++idx < len && (start + idx) < ft_strlen(s))
		copy[idx] = s[start + idx];
	copy[idx] = '\0';
	return (copy);
}
