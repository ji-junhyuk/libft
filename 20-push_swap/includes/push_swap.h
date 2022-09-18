/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:01:42 by junji             #+#    #+#             */
/*   Updated: 2022/09/18 14:40:33 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_score
{
	int	score1;
	int	score2;
	int	score3;
}	t_score;

typedef struct s_pivot_origin
{
	int	dir;
	int	pivot;
	int	push_count;
	int	cnt;
}	t_pivot_origin;

typedef struct s_node
{
	int				data;
	int				score;
	struct s_node	*next;
}	t_node;

typedef struct s_pivot_node
{
	struct s_pivot_node		*next;
	t_pivot_origin			tool;
}	t_pivot_node;

typedef struct s_list
{
	t_node	*tail;
	int		cnt;
}	t_list;

typedef struct s_pivot_list
{
	t_pivot_node	*tail;
	int				cnt;
}	t_pivot_list;

typedef struct s_pivot_new
{
	int	pivot1;
	int	pivot2;
	int	p_count;
	int	rb_count;
	int	ra_count;
	int	rrr_count;
	int	alone;
	int	flag;
}	t_pivot_new;

typedef struct s_info_input
{
	int		i;
	int		j;
	int		element_cnt;
	int		number;
	char	**element;
}	t_info_input;

void	init_list(t_list *list1, t_list *list2,
			t_list *list3, t_pivot_list *list4);
int		check_valid_input(int argc, char *argv[],
			t_list *temp, t_list *stack_a);
int		check_duplicate_list(t_list list);
int		rank_score(t_list *sorted_stack, t_list *stack_a,
			t_pivot_list *pivot_list);

#endif
