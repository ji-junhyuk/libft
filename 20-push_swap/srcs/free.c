/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:07:46 by junji             #+#    #+#             */
/*   Updated: 2022/09/18 09:10:15 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdlib.h>

int	free_split(char **copy, int idx)
{
	int	index;

	index = -1;
	while (++index < idx)
		free(copy[index]);
	free(copy);
	return (1);
}

void	free_arr(char **copy, int idx)
{
	int	index;

	index = -1;
	while (++index < idx)
		free(copy[index]);
	free(copy);
}

void	delete_pivot_node(t_pivot_list **pivot_list)
{
	t_pivot_node	*temp;
	t_pivot_node	*tail_prev;
	int				cnt;

	cnt = (*pivot_list)->cnt;
	if (cnt <= 0)
		return ;
	if (cnt == 1)
	{
		--((*pivot_list)->cnt);
		free((*pivot_list)->tail);
		(*pivot_list)->tail = NULL;
	}
	else
	{
		temp = (*pivot_list)->tail;
		tail_prev = (*pivot_list)->tail;
		while (--cnt)
			tail_prev = tail_prev->next;
		tail_prev->next = (*pivot_list)->tail->next;
		(*pivot_list)->tail = tail_prev;
		free(temp);
		temp = NULL;
		--((*pivot_list)->cnt);
	}
}

void	delete_all_stack(t_list **list)
{
	t_node	*temp;
	t_node	*tail_prev;
	int		cnt;

	if ((*list)->cnt <= 0)
		return ;
	while ((*list)->cnt > 0)
	{
		cnt = (*list)->cnt;
		temp = (*list)->tail;
		tail_prev = (*list)->tail;
		while (--cnt)
			tail_prev = tail_prev->next;
		tail_prev->next = (*list)->tail->next;
		(*list)->tail = tail_prev;
		free(temp);
		temp = NULL;
		--((*list)->cnt);
		if ((*list)->cnt == 0)
			(*list)->tail = NULL;
	}
}

void	free_stack(t_list *list1, t_list *list2)
{
	delete_all_stack(&list1);
	delete_all_stack(&list2);
}
