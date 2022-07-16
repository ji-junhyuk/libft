/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:57:15 by junji             #+#    #+#             */
/*   Updated: 2022/07/11 15:47:48 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			idx;
	unsigned char	*p;

	p = (unsigned char *)s;
	idx = -1;
	while (++idx < n)
	{
		if (p[idx] == (unsigned char)c)
			return ((void *)(p + idx));
	}
	return (0);
}
