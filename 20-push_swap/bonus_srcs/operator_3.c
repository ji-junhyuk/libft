/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 07:24:18 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:44:08 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/checker.h"

void	ra(t_list *list)
{
	if (list->cnt <= 1)
		return ;
	list->tail = list->tail->next;
}

void	rb(t_list *list)
{
	if (list->cnt <= 1)
		return ;
	list->tail = list->tail->next;
}

void	rr(t_list *list1, t_list *list2)
{
	ra(list1);
	rb(list2);
}
