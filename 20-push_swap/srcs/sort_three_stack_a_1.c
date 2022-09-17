/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three_stack_a_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:24:59 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 11:13:24 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/sort.h"
#include "../includes/print.h"

void	sort_three_a_stack_3(t_list *list1, t_list *list2, t_score score)
{
	if (score.score1 > score.score2 && score.score2 > score.score3)
	{
		pb(list1, list2);
		ra(list1);
		ra(list1);
		pa(list1, list2);
		rra(list1);
		rra(list1);
		sa(list1);
		ft_putstr("pb\n");
		ft_putstr("ra\n");
		ft_putstr("ra\n");
		ft_putstr("pa\n");
		ft_putstr("rra\n");
		ft_putstr("rra\n");
		ft_putstr("sa\n");
	}
	sort_three_a_stack_4(list1, list2, score);
}

void	sort_three_a_stack_2(t_list *list1, t_list *list2, t_score score)
{
	(void)list2;
	if (score.score2 > score.score1
		&& score.score2 > score.score3 && score.score1 > score.score3)
	{
		rra(list1);
		ft_putstr("rra\n");
	}
	else if (score.score2 > score.score1
		&& score.score2 > score.score3 && score.score3 > score.score1)
	{
		rra(list1);
		sa(list1);
		ft_putstr("rra\n");
		ft_putstr("sa\n");
	}
	else if (score.score3 > score.score1
		&& score.score3 > score.score2 && score.score1 > score.score2)
	{
		sa(list1);
		ft_putstr("sa\n");
	}
}

void	sort_three_a_stack(t_list *list1, t_list *list2)
{
	t_score	score;

	score.score1 = list_at_score(list1, 0);
	score.score2 = list_at_score(list1, 1);
	score.score3 = list_at_score(list1, 2);
	if (list1->cnt == 3)
	{
		if (score.score1 > score.score2
			&& score.score2 > score.score3)
		{
			ra(list1);
			sa(list1);
			ft_putstr("ra\n");
			ft_putstr("sa\n");
		}
		else if (score.score1 > score.score2
			&& score.score1 > score.score3 && score.score2 < score.score3)
		{
			ra(list1);
			ft_putstr("ra\n");
		}
		sort_three_a_stack_2(list1, list2, score);
	}
	else
		sort_three_a_stack_3(list1, list2, score);
}
