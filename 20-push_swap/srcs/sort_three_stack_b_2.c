/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three_stack_b_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:29:45 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:01:46 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/sort.h"
#include "../includes/print.h"

void	sort_three_b_stack_8(t_list *list1, t_list *list2, t_score score)
{
	if (score.score3 > score.score1
		&& score.score3 > score.score2 && score.score1 < score.score2)
	{
		rb(list2);
		sb(list2);
		pa(list1, list2);
		pa(list1, list2);
		rrb(list2);
		pa(list1, list2);
		ft_putstr("rb\n");
		ft_putstr("sb\n");
		ft_putstr("pa\n");
		ft_putstr("pa\n");
		ft_putstr("rrb\n");
		ft_putstr("pa\n");
	}
}

void	sort_three_b_stack_7(t_list *list1, t_list *list2, t_score score)
{
	if (score.score3 > score.score1
		&& score.score3 > score.score2 && score.score1 > score.score2)
	{
		rb(list2);
		sb(list2);
		pa(list1, list2);
		rrb(list2);
		pa(list1, list2);
		pa(list1, list2);
		ft_putstr("rb\n");
		ft_putstr("sb\n");
		ft_putstr("pa\n");
		ft_putstr("rrb\n");
		ft_putstr("pa\n");
		ft_putstr("pa\n");
	}
	sort_three_b_stack_8(list1, list2, score);
}

void	sort_three_b_stack_6(t_list *list1, t_list *list2, t_score s)
{
	if (s.score2 > s.score1 && s.score2 > s.score3 && s.score1 > s.score3)
	{
		sb(list2);
		pa(list1, list2);
		pa(list1, list2);
		pa(list1, list2);
		ft_putstr("sb\n");
		ft_putstr("pa\n");
		ft_putstr("pa\n");
		ft_putstr("pa\n");
	}
	else if (s.score2 > s.score1 && s.score2 > s.score3 && s.score1 < s.score3)
	{
		sb(list2);
		pa(list1, list2);
		sb(list2);
		pa(list1, list2);
		pa(list1, list2);
		ft_putstr("sb\n");
		ft_putstr("pa\n");
		ft_putstr("sb\n");
		ft_putstr("pa\n");
		ft_putstr("pa\n");
	}
	sort_three_b_stack_7(list1, list2, s);
}

void	sort_three_b_stack_5(t_list *list1, t_list *list2, t_score score)
{
	if (score.score1 > score.score2 && score.score2 > score.score3)
	{
		pa(list1, list2);
		pa(list1, list2);
		pa(list1, list2);
		ft_putstr("pa\n");
		ft_putstr("pa\n");
		ft_putstr("pa\n");
	}
	else if (score.score1 > score.score2
		&& score.score1 > score.score3 && score.score2 < score.score3)
	{
		pa(list1, list2);
		sb(list2);
		pa(list1, list2);
		pa(list1, list2);
		ft_putstr("pa\n");
		ft_putstr("sb\n");
		ft_putstr("pa\n");
		ft_putstr("pa\n");
	}
	sort_three_b_stack_6(list1, list2, score);
}
