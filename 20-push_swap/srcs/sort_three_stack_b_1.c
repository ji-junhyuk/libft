/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three_stack_b_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:29:01 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:03:22 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/sort.h"
#include "../includes/print.h"

void	sort_three_b_stack_4(t_list *list1, t_list *list2, t_score s)
{
	if (s.score3 > s.score1 && s.score3 > s.score2 && s.score1 > s.score2)
	{
		rrb(list2);
		pa(list1, list2);
		pa(list1, list2);
		pa(list1, list2);
		ft_putstr("rrb\n");
		ft_putstr("pa\n");
		ft_putstr("pa\n");
		ft_putstr("pa\n");
	}
	else if (s.score3 > s.score1
		&& s.score3 > s.score2 && s.score1 < s.score2)
	{
		rrb(list2);
		pa(list1, list2);
		rrb(list2);
		pa(list1, list2);
		pa(list1, list2);
		ft_putstr("rrb\n");
		ft_putstr("pa\n");
		ft_putstr("rrb\n");
		ft_putstr("pa\n");
		ft_putstr("pa\n");
	}
}

void	sort_three_b_stack_3(t_list *list1, t_list *list2, t_score score)
{
	if (score.score2 > score.score1
		&& score.score2 > score.score3 && score.score1 > score.score3)
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
	else if (score.score2 > score.score1
		&& score.score2 > score.score3 && score.score3 > score.score1)
	{
		rb(list2);
		pa(list1, list2);
		pa(list1, list2);
		pa(list1, list2);
		ft_putstr("rb\n");
		ft_putstr("pa\n");
		ft_putstr("pa\n");
		ft_putstr("pa\n");
	}
	sort_three_b_stack_4(list1, list2, score);
}

void	sort_three_b_stack_2(t_list *list1, t_list *list2, t_score score)
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
	sort_three_b_stack_3(list1, list2, score);
}

void	sort_three_b_stack(t_list *list1, t_list *list2)
{
	t_score	score;

	score.score1 = list_at_score(list2, 0);
	score.score2 = list_at_score(list2, 1);
	score.score3 = list_at_score(list2, 2);
	if (list2->cnt == 3)
		sort_three_b_stack_2(list1, list2, score);
	else
		sort_three_b_stack_5(list1, list2, score);
}
