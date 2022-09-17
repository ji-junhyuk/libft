/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three_stack_a_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:26:44 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:01:33 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include "../includes/sort.h"
#include "../includes/print.h"

void	sort_three_a_stack_5(t_list *list1, t_list *list2, t_score score)
{
	(void)list2;
	if (score.score2 > score.score1
		&& score.score2 > score.score3 && score.score3 > score.score1)
	{
		ra(list1);
		sa(list1);
		rra(list1);
		ft_putstr("ra\n");
		ft_putstr("sa\n");
		ft_putstr("rra\n");
	}
	else if (score.score3 > score.score1
		&& score.score3 > score.score2 && score.score1 > score.score2)
	{
		sa(list1);
		ft_putstr("sa\n");
	}
}

void	sort_three_a_stack_4(t_list *list1, t_list *list2, t_score score)
{
	if (score.score1 > score.score2
		&& score.score1 > score.score3 && score.score2 < score.score3)
	{
		sa(list1);
		ra(list1);
		sa(list1);
		rra(list1);
		ft_putstr("sa\n");
		ft_putstr("ra\n");
		ft_putstr("sa\n");
		ft_putstr("rra\n");
	}
	else if (score.score2 > score.score1
		&& score.score2 > score.score3 && score.score1 > score.score3)
	{
		ra(list1);
		sa(list1);
		rra(list1);
		sa(list1);
		ft_putstr("ra\n");
		ft_putstr("sa\n");
		ft_putstr("rra\n");
		ft_putstr("sa\n");
	}
	sort_three_a_stack_5(list1, list2, score);
}
