/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:00:43 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:41:59 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	rra(t_list *list)
{
	int	cnt;

	cnt = list->cnt;
	if (list->cnt <= 1)
		return ;
	while (--cnt)
		list->tail = list->tail->next;
}

void	rrb(t_list *list)
{
	int	cnt;

	cnt = list->cnt;
	if (list->cnt <= 1)
		return ;
	while (--cnt)
		list->tail = list->tail->next;
}

void	rrr(t_list *list1, t_list *list2)
{
	rra(list1);
	rrb(list2);
}
