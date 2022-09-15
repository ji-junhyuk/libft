/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:01:42 by junji             #+#    #+#             */
/*   Updated: 2022/09/15 15:33:39 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# define ERROR_MESSAGE "Error\n"

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

size_t	ft_strlen(char *str);
void	ft_putstr(char *str);
void	put_error(char *str);

int		count_word(char *str);
int		find_word_len(char *str);
void	skip_space(char **str);
char	**ft_split(char *str);

void	*ft_memset(void *b, int c, size_t len);
void	init_list(t_list *list1, t_list *list2,
			t_list *list3, t_pivot_list *list4);
void	init_pivot_list(t_pivot_list *list);
void	init_pivot_new(t_pivot_new	*tool2);

int		ft_swap(t_list *list, int left, int right);
int		list_at(t_list *list, int left);
void	quick_sort(t_list *list, int start, int end);
void	mark_rank(t_list *temp, t_list *list);
int		rank_score(t_list *sorted_stack, t_list *stack_a,
			t_pivot_list *pivot_list);

void	free_arr(char **copy, int idx);
void	free_stack(t_list *list1, t_list *list2);
void	delete_all_stack(t_list **list);
void	delete_pivot_node(t_pivot_list **pivot_list);

int		ft_atoi(char *str);
int		check_valid_input(int argc, char *argv[],
			t_list *temp, t_list *stack_a);
int		check_real_zero(char *str);
int		check_duplicate_list(t_list list);

int		insert_list(t_list *list, int number);
int		insert_pivot_list(t_pivot_list *list,
			int dir, int pivot, int push_count);

int		pb(t_list *list1, t_list *list2);
int		pa(t_list *list1, t_list *list2);
int		insert_front_list(t_list *list, t_node *cur);
int		sa(t_list *list);
int		sb(t_list *list);

int		ss(t_list *list1, t_list *list2);
int		ra(t_list *list);
int		rb(t_list *list);
int		rr(t_list *list1, t_list *list2);

int		rra(t_list *list);
int		rrb(t_list *list);
int		rrr(t_list *list1, t_list *list2);

void	sort_two_a_stack(t_list *list1, t_list *list2);
void	sort_two_b_stack2(t_list *list1, t_list *list2, t_score score);
void	sort_two_b_stack(t_list *list1, t_list *list2);

void	sort_three_a_stack_5(t_list *list1, t_list *list2, t_score score);
void	sort_three_a_stack_4(t_list *list1, t_list *list2, t_score score);

void	sort_three_a_stack_3(t_list *list1, t_list *list2, t_score score);
void	sort_three_a_stack_2(t_list *list1, t_list *list2, t_score score);
void	sort_three_a_stack(t_list *list1, t_list *list2);


void	sort_three_b_stack_8(t_list *list1, t_list *list2, t_score score);
void	sort_three_b_stack_7(t_list *list1, t_list *list2, t_score score);
void	sort_three_b_stack_6(t_list *list1, t_list *list2, t_score s);
void	sort_three_b_stack_5(t_list *list1, t_list *list2, t_score score);

void	sort_three_b_stack_4(t_list *list1, t_list *list2, t_score s);

void	sort_three_b_stack_3(t_list *list1, t_list *list2, t_score score);
void	sort_three_b_stack_2(t_list *list1, t_list *list2, t_score score);
void	sort_three_b_stack(t_list *list1, t_list *list2);

void	rotate_stack_a(t_list *list1, t_list *list2,
			int ra_count, int rb_count);
void	rotate_stack_b(t_list *list1, t_list *list2,
			int ra_count, int rb_count);
void	rotate_a(t_list *list1, t_list *list2, t_pivot_new *new_pivot);
void	rotate_b(t_list *list1, t_list *list2, t_pivot_new *new_pivot);
void	rotate_pivot(t_list *list1, t_list *list2, t_pivot_list **pivot_list);

void	use_one_pivot_a_to_b_2(t_list *list, t_pivot_new *pivot_new);
void	use_one_pivot_a_to_b(t_list *list1, t_list *list2,
			t_pivot_origin *pivot_origin, t_pivot_new *pivot_new);
int		insert_pivot_list_a_to_b_6(t_pivot_list **pivot_list,
			t_pivot_origin *old_pivot, t_pivot_new *new_pivot);

int		push_a_to_b_2(t_pivot_list **pivot_list,
			t_pivot_origin *old_pivot, t_pivot_new *new_pivot);
int		push_a_to_b(t_list *list1, t_list *list2, t_pivot_list **pivot_list);
void	use_two_pivot_a_to_b_2(t_list *list1, t_list *list2,
			t_pivot_new *pivot_new);

void	find_two_pivot_alone(t_list *list,
			t_pivot_origin *old_pivot, t_pivot_new *new_pivot);

void	use_two_pivot_a_to_b(t_list *list1, t_list *list2,
			t_pivot_origin *pivot_origin, t_pivot_new *pivot_new);

int		push_b_to_a(t_list *list1, t_list *list2, t_pivot_list **pivot_list);
int		push_b_to_a_2(t_pivot_list **pivot_list,
			t_pivot_origin *old_pivot, t_pivot_new *new_pivot);
void	use_two_pivot_b_to_a(t_list *list1, t_list *list2,
			t_pivot_origin *pivot_origin, t_pivot_new *pivot_new);

void	use_one_pivot_b_to_a_2(t_list *list, t_pivot_new *pivot_new);
void	use_one_pivot_b_to_a(t_list *list1, t_list *list2,
			t_pivot_origin *pivot_origin, t_pivot_new *pivot_new);
int		insert_pivot_list_b_to_a_6(t_pivot_list **pivot_list,
			t_pivot_origin *old_pivot, t_pivot_new *new_pivot);

int		list_at_score(t_list *list, int left);
int		is_sorted(t_list *list);
void	sort_list(t_list *list1, t_list *list2, int dir, int count);
int		recur(t_list *list1, t_list *list2, t_pivot_list *pivot_list);
#endif
