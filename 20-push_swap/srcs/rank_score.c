/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rank_score.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:54:26 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 09:50:13 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/memory.h"

int	list_at(t_list *list, int left)
{
	t_node	*first;

	if (list->cnt <= 0)
		return (0);
	first = list->tail->next;
	while (left--)
		first = first->next;
	return (first->data);
}

int	ft_swap(t_list *list, int left, int right)
{
	int		temp;
	t_node	*first;
	t_node	*second;

	if (list->cnt <= 1)
		return (1);
	first = list->tail->next;
	second = list->tail->next;
	while (left--)
		first = first->next;
	temp = first->data;
	while (right--)
		second = second->next;
	first->data = second->data;
	second->data = temp;
	return (0);
}

void	quick_sort(t_list *list, int start, int end)
{
	int	pivot;
	int	left;
	int	right;

	pivot = start;
	left = start + 1;
	right = end;
	if (start >= end)
		return ;
	while (left <= right)
	{
		while (left <= end && list_at(list, left) <= list_at(list, pivot))
			++left;
		while (right > start && list_at(list, right) >= list_at(list, pivot))
			--right;
		if (left > right)
			ft_swap(list, pivot, right);
		else
			ft_swap(list, left, right);
	}
	quick_sort(list, start, right - 1);
	quick_sort(list, right + 1, end);
}

void	mark_rank(t_list *temp, t_list *list)
{
	int		score;
	int		temp_cnt;
	int		list_cnt;
	t_node	*cur;
	t_node	*temp_cur;

	if (list->cnt <= 0)
		return ;
	score = 1;
	temp_cur = temp->tail->next;
	cur = list->tail->next;
	temp_cnt = temp->cnt;
	list_cnt = list->cnt;
	while (temp_cnt--)
	{
		list_cnt = list->cnt;
		cur = list->tail->next;
		while (list_cnt--)
		{
			if (cur->data == temp_cur->data)
				cur->score = score++;
			cur = cur->next;
		}
		temp_cur = temp_cur->next;
	}
}

int	rank_score(t_list *sorted_stack, t_list *stack_a, t_pivot_list *pivot_list)
{
	quick_sort(sorted_stack, 0, sorted_stack->cnt - 1);
	mark_rank(sorted_stack, stack_a);
	if (insert_pivot_list(pivot_list, 0, stack_a->cnt, stack_a->cnt) == 1)
		return (1);
	return (0);
}
