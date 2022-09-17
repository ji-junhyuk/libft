/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:30:49 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:03:58 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/sort.h"
#include "../includes/print.h"
#include "../includes/memory.h"

void	rotate_stack_a(t_list *list1, t_list *list2, int ra_count, int rb_count)
{
	int	rrr_count;

	rrr_count = rb_count;
	while (--rrr_count >= 0)
	{
		rrr(list1, list2);
		ft_putstr("rrr\n");
	}
	ra_count -= rb_count;
	while (--ra_count >= 0)
	{
		rra(list1);
		ft_putstr("rra\n");
	}
}

void	rotate_stack_b(t_list *list1, t_list *list2, int ra_count, int rb_count)
{
	int	rrr_count;

	rrr_count = ra_count;
	while (--rrr_count >= 0)
	{
		rrr(list1, list2);
		ft_putstr("rrr\n");
	}
	rb_count -= ra_count;
	while (--rb_count >= 0)
	{
		rrb(list2);
		ft_putstr("rrb\n");
	}
}

void	rotate_a(t_list *list1, t_list *list2, t_pivot_new *new_pivot)
{
	int	rrr_count;
	int	ra_count;
	int	rb_count;

	ra_count = new_pivot->ra_count;
	rb_count = new_pivot->rb_count;
	rrr_count = new_pivot->rb_count;
	while (--rrr_count >= 0)
	{
		rrr(list1, list2);
		ft_putstr("rrr\n");
	}
	ra_count -= rb_count;
	while (new_pivot->alone == 0 && --ra_count >= 0)
	{
		rra(list1);
		ft_putstr("rra\n");
	}
}

void	rotate_b(t_list *list1, t_list *list2, t_pivot_new *new_pivot)
{
	int	rrr_count;
	int	ra_count;
	int	rb_count;

	ra_count = new_pivot->ra_count;
	rb_count = new_pivot->rb_count;
	rrr_count = new_pivot->ra_count;
	while (--rrr_count >= 0)
	{
		rrr(list1, list2);
		ft_putstr("rrr\n");
	}
	rb_count -= ra_count;
	while (new_pivot->alone == 0 && --rb_count >= 0)
	{
		rrb(list2);
		ft_putstr("rrb\n");
	}
}

void	rotate_pivot(t_list *list1, t_list *list2,
	t_pivot_list **pivot_list)
{
	t_pivot_origin	tool;
	int				ra_count;
	int				rb_count;

	tool = (*pivot_list)->tail->tool;
	ra_count = tool.pivot;
	rb_count = tool.push_count;
	if (ra_count <= rb_count)
		rotate_stack_b(list1, list2, ra_count, rb_count);
	else if (ra_count > rb_count)
		rotate_stack_a(list1, list2, ra_count, rb_count);
	delete_pivot_node(pivot_list);
}
