/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:18:15 by junji             #+#    #+#             */
/*   Updated: 2022/07/09 14:18:18 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcat(char *dest, const char *src)
{
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*copy;
	size_t	size;

	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2);
	copy = malloc(sizeof(char) * (size + 1));
	if (!copy)
		return (0);
	copy[0] = '\0';
	ft_strcat(copy, s1);
	ft_strcat(copy, s2);
	return (copy);
}
