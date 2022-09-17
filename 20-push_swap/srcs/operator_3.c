/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:20:36 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:41:35 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ra(t_list *list)
{
	if (list->cnt <= 1)
		return ;
	list->tail = list->tail->next;
	return ;
}

void	rb(t_list *list)
{
	if (list->cnt <= 1)
		return ;
	list->tail = list->tail->next;
	return ;
}

void	rr(t_list *list1, t_list *list2)
{
	ra(list1);
	rb(list2);
}
