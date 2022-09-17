/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:17:43 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:40:17 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdlib.h>

void	insert_front_list(t_list *list, t_node *cur)
{
	if (list->tail == NULL)
	{
		list->tail = cur;
		cur->next = cur;
	}
	else
	{
		cur->next = list->tail->next;
		list->tail->next = cur;
	}
	++(list->cnt);
}

void	pb(t_list *list1, t_list *list2)
{
	t_node	*cur;

	if (list1->cnt <= 0)
		return ;
	if (list1->cnt == 1)
	{
		cur = list1->tail;
		list1->tail = NULL;
		--(list1->cnt);
		insert_front_list(list2, cur);
		return ;
	}
	cur = list1->tail->next;
	list1->tail->next = list1->tail->next->next;
	--(list1->cnt);
	insert_front_list(list2, cur);
	return ;
}

void	pa(t_list *list1, t_list *list2)
{
	t_node	*cur;

	if (list2->cnt <= 0)
		return ;
	if (list2->cnt == 1)
	{
		cur = list2->tail;
		list2->tail = NULL;
		--(list2->cnt);
		insert_front_list(list1, cur);
		return ;
	}
	cur = list2->tail->next;
	list2->tail->next = list2->tail->next->next;
	--(list2->cnt);
	insert_front_list(list1, cur);
	return ;
}
