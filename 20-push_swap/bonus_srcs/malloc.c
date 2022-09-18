/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 07:58:08 by junji             #+#    #+#             */
/*   Updated: 2022/09/18 09:22:06 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/checker.h"
#include <stdlib.h>

int	insert_list(t_list *list, int number)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (1);
	new_node->data = number;
	if (list->tail == NULL)
	{
		list->tail = new_node;
		new_node->next = new_node;
	}
	else
	{
		new_node->next = list->tail->next;
		list->tail->next = new_node;
		list->tail = new_node;
	}
	++(list->cnt);
	return (0);
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
