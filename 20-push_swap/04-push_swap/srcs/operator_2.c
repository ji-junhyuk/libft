/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:20:10 by junji             #+#    #+#             */
/*   Updated: 2022/09/15 20:41:02 by jijunhyuk        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ss(t_list *list1, t_list *list2)
{
	sa(list1);
	sb(list2);
	return (0);
}

int	ra(t_list *list)
{
	if (list->cnt <= 1)
		return (0);
	list->tail = list->tail->next;
	return (0);
}

int	rb(t_list *list)
{
	if (list->cnt <= 1)
		return (0);
	list->tail = list->tail->next;
	return (0);
}

int	rr(t_list *list1, t_list *list2)
{
	ra(list1);
	rb(list2);
	return (0);
}
