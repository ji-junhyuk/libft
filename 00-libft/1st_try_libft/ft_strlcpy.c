/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:00:49 by junji             #+#    #+#             */
/*   Updated: 2022/07/09 14:00:53 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	cnt;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	cnt = 1;
	while (*src && ++cnt <= dstsize)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}
