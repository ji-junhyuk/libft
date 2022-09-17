/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b_to_a.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:41:07 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:04:07 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/memory.h"
#include "../includes/sort.h"
#include "../includes/print.h"

void	use_two_pivot_b_to_a(t_list *list1, t_list *list2,
		t_pivot_origin *pivot_origin, t_pivot_new *pivot_new)
{
	find_two_pivot_alone(list1, pivot_origin, pivot_new);
	pivot_origin->cnt = pivot_origin->push_count;
	while (--(pivot_origin->cnt) >= 0)
	{
		if (list_at_score(list2, 0) > pivot_new->pivot2)
		{
			pa(list1, list2);
			++pivot_new->p_count;
			ft_putstr("pa\n");
			if (list_at_score(list1, 0) <= pivot_new->pivot1 && list1->cnt > 1)
			{
				ra(list1);
				ft_putstr("ra\n");
				++pivot_new->ra_count;
			}
		}
		else
		{
			rb(list2);
			++pivot_new->rb_count;
			ft_putstr("rb\n");
		}
	}
}

int	push_b_to_a_2(t_pivot_list **pivot_list,
	t_pivot_origin *old_pivot, t_pivot_new *new_pivot)
{
	if (insert_pivot_list(*pivot_list, 1,
			new_pivot->pivot2, new_pivot->rb_count) == 1)
		return (1);
	if (insert_pivot_list(*pivot_list, 0,
			new_pivot->pivot1, new_pivot->ra_count) == 1)
		return (1);
	if (insert_pivot_list(*pivot_list, 2,
			new_pivot->ra_count, new_pivot->rb_count) == 1)
		return (1);
	if (insert_pivot_list(*pivot_list, 0, old_pivot->pivot,
			new_pivot->p_count - new_pivot->ra_count) == 1)
		return (1);
	return (0);
}

int	push_b_to_a(t_list *list1, t_list *list2, t_pivot_list **pivot_list)
{
	t_pivot_origin		old_pivot;
	t_pivot_new			new_pivot;

	old_pivot = (*pivot_list)->tail->tool;
	if (old_pivot.push_count <= 3)
	{
		sort_list(list1, list2, old_pivot.dir, old_pivot.push_count);
		delete_pivot_node(pivot_list);
		return (0);
	}
	ft_memset(&new_pivot, 0, sizeof(new_pivot));
	delete_pivot_node(pivot_list);
	if (old_pivot.push_count <= 6)
	{
		use_one_pivot_b_to_a(list1, list2, &old_pivot, &new_pivot);
		if (insert_pivot_list_b_to_a_6(pivot_list, &old_pivot, &new_pivot) == 1)
			return (1);
	}
	else
	{
		use_two_pivot_b_to_a(list1, list2, &old_pivot, &new_pivot);
		if (push_b_to_a_2(pivot_list, &old_pivot, &new_pivot) == 1)
			return (1);
	}
	return (0);
}
