/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a_to_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:00:27 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:00:37 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/memory.h"
#include "../includes/sort.h"
#include "../includes/print.h"

void	find_two_pivot_alone(t_list *list,
		t_pivot_origin *old_pivot, t_pivot_new *new_pivot)
{
	new_pivot->pivot1 = old_pivot->pivot - old_pivot->push_count / 3;
	new_pivot->pivot2 = old_pivot->pivot - old_pivot->push_count / 3 * 2;
	if (list->cnt == old_pivot->push_count)
		new_pivot->alone = 1;
}

void	use_two_pivot_a_to_b_2(t_list *list1, t_list *list2,
		t_pivot_new *pivot_new)
{
	if (pivot_new->ra_count <= pivot_new->rb_count)
		rotate_b(list1, list2, pivot_new);
	else
		rotate_a(list1, list2, pivot_new);
}

void	use_two_pivot_a_to_b(t_list *list1, t_list *list2,
		t_pivot_origin *pivot_origin, t_pivot_new *pivot_new)
{
	find_two_pivot_alone(list1, pivot_origin, pivot_new);
	pivot_origin->cnt = pivot_origin->push_count;
	while (--(pivot_origin->cnt) >= 0)
	{
		if (list_at_score(list1, 0) <= pivot_new->pivot1)
		{
			pb(list1, list2);
			++pivot_new->p_count;
			ft_putstr("pb\n");
			if (list_at_score(list2, 0) > pivot_new->pivot2)
			{
				rb(list2);
				ft_putstr("rb\n");
				++pivot_new->rb_count;
			}
		}
		else
		{
			ra(list1);
			++pivot_new->ra_count;
			ft_putstr("ra\n");
		}
	}
	use_two_pivot_a_to_b_2(list1, list2, pivot_new);
}

int	push_a_to_b_2(t_pivot_list **pivot_list,
		t_pivot_origin *old_pivot, t_pivot_new *new_pivot)
{
	if (insert_pivot_list(*pivot_list, 1,
			new_pivot->pivot2, new_pivot->p_count - new_pivot->rb_count) == 1)
		return (1);
	if (insert_pivot_list(*pivot_list, 1,
			new_pivot->pivot1, new_pivot->rb_count))
		return (1);
	if (insert_pivot_list(*pivot_list, 0,
			old_pivot->pivot, old_pivot->push_count - new_pivot->p_count) == 1)
		return (1);
	return (0);
}

int	push_a_to_b(t_list *list1, t_list *list2, t_pivot_list **pivot_list)
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
		use_one_pivot_a_to_b(list1, list2, &old_pivot, &new_pivot);
		if (insert_pivot_list_a_to_b_6(pivot_list, &old_pivot, &new_pivot) == 1)
			return (1);
	}
	else
	{
		use_two_pivot_a_to_b(list1, list2, &old_pivot, &new_pivot);
		if (push_a_to_b_2(pivot_list, &old_pivot, &new_pivot) == 1)
			return (1);
	}
	return (0);
}
