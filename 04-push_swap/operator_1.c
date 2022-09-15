/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:17:43 by junji             #+#    #+#             */
/*   Updated: 2022/09/15 14:53:57 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	pb(t_list *list1, t_list *list2)
{
	t_node	*cur;

	if (list1->cnt <= 0)
		return (0);
	if (list1->cnt == 1)
	{
		cur = list1->tail;
		list1->tail = NULL;
		--(list2->cnt);
		insert_front_list(list2, cur);
		return (0);
	}
	cur = list1->tail->next;
	list1->tail->next = list1->tail->next->next;
	--(list1->cnt);
	insert_front_list(list2, cur);
	return (0);
}

int	pa(t_list *list1, t_list *list2)
{
	t_node	*cur;

	if (list2->cnt <= 0)
		return (0);
	if (list2->cnt == 1)
	{
		cur = list2->tail;
		list2->tail = NULL;
		--(list2->cnt);
		insert_front_list(list1, cur);
		return (0);
	}
	cur = list2->tail->next;
	list2->tail->next = list2->tail->next->next;
	--(list2->cnt);
	insert_front_list(list1, cur);
	return (0);
}

int	insert_front_list(t_list *list, t_node *cur)
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
	return (0);
}

int	sa(t_list *list)
{
	t_node	*tail_prev;
	t_node	*temp;
	int		cnt;

	cnt = 3;
	temp = list->tail->next;
	tail_prev = list->tail;
	if (list->cnt <= 1)
		return (0);
	while (--cnt >= 0)
		tail_prev = tail_prev->next;
	if (list->cnt == 2)
	{
		list->tail = list->tail->next;
		return (0);
	}
	else
	{
		list->tail->next = list->tail->next->next;
		list->tail->next->next = temp;
		temp->next = tail_prev;
		return (0);
	}
	return (0);
}

int	sb(t_list *list)
{
	t_node	*tail_prev;
	t_node	*temp;
	int		cnt;

	cnt = 3;
	temp = list->tail->next;
	tail_prev = list->tail;
	if (list->cnt <= 1)
		return (0);
	while (--cnt >= 0)
		tail_prev = tail_prev->next;
	if (list->cnt == 2)
	{
		list->tail = list->tail->next;
		return (0);
	}
	else
	{
		list->tail->next = list->tail->next->next;
		list->tail->next->next = temp;
		temp->next = tail_prev;
		return (0);
	}
	return (0);
}
