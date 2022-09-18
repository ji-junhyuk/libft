/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:06:04 by junji             #+#    #+#             */
/*   Updated: 2022/09/18 14:36:21 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/print.h"
#include "../includes/sort.h"
#include "../includes/memory.h"

int	is_sorted(t_list *list)
{
	int		cnt;
	t_node	*cur;

	if (list->cnt <= 1)
		return (1);
	cnt = list->cnt;
	cur = list->tail->next;
	while (--cnt)
	{
		if (cur->data > cur->next->data)
			return (0);
		cur = cur->next;
	}
	return (1);
}

int	list_at_score(t_list *list, int left)
{
	t_node	*first;

	if (list->cnt <= 0)
		return (0);
	first = list->tail->next;
	while (left--)
		first = first->next;
	return (first->score);
}

void	sort_list(t_list *list1, t_list *list2, int dir, int count)
{
	if (count == 3)
	{
		if (dir == 0)
			sort_three_a_stack(list1, list2);
		else
			sort_three_b_stack(list1, list2);
	}
	else if (count == 2)
	{
		if (dir == 0)
			sort_two_a_stack(list1, list2);
		else
			sort_two_b_stack(list1, list2);
	}
	else if (count == 1)
	{
		if (dir == 1)
		{
			pa(list1, list2);
			ft_putstr("pa\n");
		}
	}
}

int	recur(t_list *list1, t_list *list2, t_pivot_list *pivot_list)
{
	t_pivot_node	*cur;

	while (pivot_list->cnt > 0)
	{
		if (is_sorted(list1) == 1 && list2->cnt == 0)
			break ;
		cur = pivot_list->tail;
		if (cur->tool.dir == 0)
		{
			if (push_a_to_b(list1, list2, &pivot_list) == 1)
				return (1);
		}
		else if (cur->tool.dir == 1)
		{
			if (push_b_to_a(list1, list2, &pivot_list) == 1)
				return (1);
		}
		else if (cur->tool.dir == 2)
			rotate_pivot(list1, list2, &pivot_list);
	}
	delete_pivot_node(&pivot_list);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_list			stack_a;
	t_list			stack_b;
	t_list			sorted_stack;
	t_pivot_list	pivot_list;

	init_list(&stack_a, &stack_b, &sorted_stack, &pivot_list);
	if (argc == 1)
		return (0);
	if (check_valid_input(argc, argv, &sorted_stack, &stack_a) == 1)
		put_error(ERROR_MESSAGE);
	if (check_duplicate_list(stack_a) == 1)
		put_error(ERROR_MESSAGE);
	if (rank_score(&sorted_stack, &stack_a, &pivot_list) == 1)
		put_error(ERROR_MESSAGE);
	if (recur(&stack_a, &stack_b, &pivot_list) == 1)
		put_error(ERROR_MESSAGE);
	free_stack(&stack_a, &sorted_stack);
	return (0);
}
