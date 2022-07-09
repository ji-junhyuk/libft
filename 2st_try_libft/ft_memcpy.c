/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:57:46 by junji             #+#    #+#             */
/*   Updated: 2022/07/09 13:57:49 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			idx;
	unsigned char	*p1;
	unsigned char	*p2;

	if (dst == src)
		return (dst);
	p1 = (unsigned char *)dst;
	p2 = (unsigned char *)src;
	idx = -1;
	while (++idx < n)
		p1[idx] = p2[idx];
	return (dst);
}
