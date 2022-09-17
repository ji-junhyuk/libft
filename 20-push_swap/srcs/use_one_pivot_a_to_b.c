/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_one_pivot_a_to_b.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:34:20 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 11:23:31 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/sort.h"
#include "../includes/print.h"
#include "../includes/memory.h"

int	insert_pivot_list_a_to_b_6(t_pivot_list **pivot_list,
		t_pivot_origin *old_pivot, t_pivot_new *new_pivot)
{
	if (insert_pivot_list(*pivot_list, 1,
			new_pivot->pivot1, new_pivot->p_count) == 1)
		return (1);
	if (insert_pivot_list(*pivot_list, 0,
			old_pivot->pivot, old_pivot->push_count - new_pivot->p_count) == 1)
		return (1);
	return (0);
}

void	use_one_pivot_a_to_b_2(t_list *list, t_pivot_new *pivot_new)
{
	if (!(pivot_new->alone))
	{
		while (--(pivot_new->ra_count) >= 0)
		{
			rra(list);
			ft_putstr("rra\n");
		}
	}
}

void	use_one_pivot_a_to_b(t_list *list1, t_list *list2,
		t_pivot_origin *pivot_origin, t_pivot_new *pivot_new)
{
	int	cnt;

	cnt = pivot_origin->push_count;
	if (pivot_origin->push_count == list1->cnt)
		pivot_new->alone = 1;
	pivot_new->pivot1 = pivot_origin->pivot - pivot_origin->push_count / 2;
	while (--cnt >= 0)
	{
		if (list_at_score(list1, 0) <= pivot_new->pivot1)
		{
			pb(list1, list2);
			ft_putstr("pb\n");
			++(pivot_new->p_count);
		}
		else
		{
			ra(list1);
			ft_putstr("ra\n");
			++(pivot_new->ra_count);
		}
	}
	use_one_pivot_a_to_b_2(list1, pivot_new);
}
