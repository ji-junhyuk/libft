/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:47:01 by junji             #+#    #+#             */
/*   Updated: 2022/09/17 14:47:01 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include "push_swap.h"

int		push_a_to_b(t_list *list1, t_list *list2,
			t_pivot_list **pivot_list);
int		push_b_to_a(t_list *list1, t_list *list2,
			t_pivot_list **pivot_list);
void	rotate_pivot(t_list *list1, t_list *list2,
			t_pivot_list **pivot_list);

void	rotate_b(t_list *list1, t_list *list2, t_pivot_new *new_pivot);
void	rotate_a(t_list *list1, t_list *list2, t_pivot_new *new_pivot);

int		list_at_score(t_list *list, int left);
void	sort_list(t_list *list1, t_list *list2, int dir, int count);
void	find_two_pivot_alone(t_list *list,
			t_pivot_origin *old_pivot, t_pivot_new *new_pivot);

void	pb(t_list *list1, t_list *list2);
void	pa(t_list *list1, t_list *list2);
void	sa(t_list *list);
void	sb(t_list *list);
void	ss(t_list *list1, t_list *list2);
void	ra(t_list *list);
void	rb(t_list *list);
void	rr(t_list *list1, t_list *list2);
void	rra(t_list *list);
void	rrb(t_list *list);
void	rrr(t_list *list1, t_list *list2);

int		insert_front_list(t_list *list, t_node *cur);
int		insert_front_list(t_list *list, t_node *cur);
void	use_one_pivot_a_to_b(t_list *list1, t_list *list2,
			t_pivot_origin *pivot_origin, t_pivot_new *pivot_new);
void	use_one_pivot_b_to_a(t_list *list1, t_list *list2,
			t_pivot_origin *pivot_origin, t_pivot_new *pivot_new);

void	sort_three_a_stack_4(t_list *list1, t_list *list2, t_score score);
void	sort_three_b_stack_5(t_list *list1, t_list *list2, t_score score);
void	sort_three_a_stack(t_list *list1, t_list *list2);
void	sort_three_b_stack(t_list *list1, t_list *list2);
void	sort_two_a_stack(t_list *list1, t_list *list2);
void	sort_two_b_stack(t_list *list1, t_list *list2);

#endif
