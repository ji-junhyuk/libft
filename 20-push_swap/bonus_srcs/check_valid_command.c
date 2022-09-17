/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 08:11:27 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 09:11:40 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/checker.h"
#include "../bonus_includes/sort.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	cnt;

	if (n == 0)
		return (0);
	cnt = 0;
	while (*s1 && (*s1 == *s2) && ++cnt < n)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

int	check_valid_command(t_list *list1, t_list *list2, char *cmd)
{
	if (ft_strncmp(cmd, "sa\n", 3) == 0)
		sa(list1);
	else if (ft_strncmp(cmd, "sb\n", 3) == 0)
		sb(list2);
	else if (ft_strncmp(cmd, "ss\n", 3) == 0)
		ss(list1, list2);
	else if (ft_strncmp(cmd, "pa\n", 3) == 0)
		pa(list1, list2);
	else if (ft_strncmp(cmd, "pb\n", 3) == 0)
		pb(list1, list2);
	else if (ft_strncmp(cmd, "ra\n", 3) == 0)
		ra(list1);
	else if (ft_strncmp(cmd, "rb\n", 3) == 0)
		rb(list2);
	else if (ft_strncmp(cmd, "rra\n", 4) == 0)
		rra(list1);
	else if (ft_strncmp(cmd, "rrb\n", 4) == 0)
		rrb(list2);
	else if (ft_strncmp(cmd, "rrr\n", 4) == 0)
		rrr(list1, list2);
	else if (ft_strncmp(cmd, "rr\n", 3) == 0)
		rr(list1, list2);
	else
		return (1);
	return (0);
}
