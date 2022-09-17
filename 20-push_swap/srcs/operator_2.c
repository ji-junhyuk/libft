/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:20:10 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:41:07 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sa(t_list *list)
{
	t_node	*tail_prev;
	t_node	*temp;
	int		cnt;

	cnt = 3;
	temp = list->tail->next;
	tail_prev = list->tail;
	if (list->cnt <= 1)
		return ;
	while (--cnt >= 0)
		tail_prev = tail_prev->next;
	if (list->cnt == 2)
		list->tail = list->tail->next;
	else
	{
		list->tail->next = list->tail->next->next;
		list->tail->next->next = temp;
		temp->next = tail_prev;
	}
}

void	sb(t_list *list)
{
	t_node	*tail_prev;
	t_node	*temp;
	int		cnt;

	cnt = 3;
	temp = list->tail->next;
	tail_prev = list->tail;
	if (list->cnt <= 1)
		return ;
	while (--cnt >= 0)
		tail_prev = tail_prev->next;
	if (list->cnt == 2)
		list->tail = list->tail->next;
	else
	{
		list->tail->next = list->tail->next->next;
		list->tail->next->next = temp;
		temp->next = tail_prev;
	}
}

void	ss(t_list *list1, t_list *list2)
{
	sa(list1);
	sb(list2);
}
