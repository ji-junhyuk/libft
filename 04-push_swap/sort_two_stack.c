/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_two_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:21:16 by junji             #+#    #+#             */
/*   Updated: 2022/09/15 15:28:58 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_two_a_stack(t_list *list1, t_list *list2)
{
	(void)list2;
	int	score1;
	int	score2;

	score1 = list_at_score(list1, 0);
	score2 = list_at_score(list1, 1);
	if (score1 > score2)
	{
		ft_putstr("sa\n");
		sa(list1);
	}
}

void	sort_two_b_stack2(t_list *list1, t_list *list2, t_score score)
{
	if (score.score1 < score.score2)
	{
		rb(list2);
		pa(list1, list2);
		rrb(list2);
		pa(list1, list2);
		ft_putstr("rb\n");
		ft_putstr("pa\n");
		ft_putstr("rrb\n");
		ft_putstr("pa\n");
	}
	else
	{
		pa(list1, list2);
		pa(list1, list2);
		ft_putstr("pa\n");
		ft_putstr("pa\n");
	}
}

void	sort_two_b_stack(t_list *list1, t_list *list2)
{
	t_score	score;

	score.score1 = list_at_score(list2, 0);
	score.score2 = list_at_score(list2, 1);
	if (list2->cnt == 2)
	{
		if (score.score1 < score.score2)
		{
			rb(list2);
			pa(list1, list2);
			pa(list1, list2);
			ft_putstr("rb\n");
			ft_putstr("pa\n");
			ft_putstr("pa\n");
		}
		else
		{
			pa(list1, list2);
			pa(list1, list2);
			ft_putstr("pa\n");
			ft_putstr("pa\n");
		}
	}
	else
		sort_two_b_stack2(list1, list2, score);
}
