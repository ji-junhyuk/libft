/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:53:36 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:02:28 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	size_t			idx;

	idx = -1;
	p = (unsigned char *)b;
	while (++idx < len)
		p[idx] = c;
	return (b);
}

void	init_pivot_list(t_pivot_list *list)
{
	list->tail = NULL;
	list->cnt = 0;
}

void	init_pivot_new(t_pivot_new	*tool2)
{
	tool2->pivot1 = 0;
	tool2->pivot2 = 0;
	tool2->p_count = 0;
	tool2->ra_count = 0;
	tool2->rb_count = 0;
	tool2->rrr_count = 0;
	tool2->alone = 0;
	tool2->flag = 0;
}

void	init_list(t_list *list1, t_list *list2,
		t_list *list3, t_pivot_list *list4)
{
	ft_memset(list1, 0, sizeof(*list1));
	ft_memset(list2, 0, sizeof(*list2));
	ft_memset(list3, 0, sizeof(*list3));
	ft_memset(list4, 0, sizeof(*list4));
}
