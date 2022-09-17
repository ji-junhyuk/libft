/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 07:22:50 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:43:08 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/checker.h"

void	sa(t_list *list)
{
	t_node	*tail_prev;
	t_node	*temp;
	int		cnt;

	cnt = 3;
	if (list->cnt <= 1)
		return ;
	temp = list->tail->next;
	tail_prev = list->tail;
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
	if (list->cnt <= 1)
		return ;
	temp = list->tail->next;
	tail_prev = list->tail;
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
