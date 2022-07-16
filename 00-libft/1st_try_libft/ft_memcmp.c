/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:58:11 by junji             #+#    #+#             */
/*   Updated: 2022/07/09 13:58:17 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			idx;
	size_t			cnt;
	unsigned char	*p1;
	unsigned char	*p2;

	if (n == 0)
		return (0);
	idx = 0;
	cnt = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (++cnt < n && p1[idx] == p2[idx])
		++idx;
	return (p1[idx] - p2[idx]);
}
