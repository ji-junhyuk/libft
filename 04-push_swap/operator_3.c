/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:20:36 by junji             #+#    #+#             */
/*   Updated: 2022/09/15 14:54:06 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rra(t_list *list)
{
	int	cnt;

	cnt = list->cnt;
	if (list->cnt <= 1)
		return (0);
	while (--cnt)
		list->tail = list->tail->next;
	return (0);
}

int	rrb(t_list *list)
{
	int	cnt;

	cnt = list->cnt;
	if (list->cnt <= 1)
		return (0);
	while (--cnt)
		list->tail = list->tail->next;
	return (0);
}

int	rrr(t_list *list1, t_list *list2)
{
	rra(list1);
	rrb(list2);
	return (0);
}
