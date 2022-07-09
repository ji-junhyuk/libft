/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:00:25 by junji             #+#    #+#             */
/*   Updated: 2022/07/09 14:00:29 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*s1;
	const unsigned char	*s2;
	size_t				idx;

	s1 = dst;
	s2 = src;
	if (dst == src || len == 0)
		return (dst);
	if (s1 <= s2)
	{
		idx = -1;
		while (++idx < len)
			s1[idx] = s2[idx];
	}
	else
	{
		while (len-- > 0)
			s1[len] = s2[len];
	}
	return (dst);
}
