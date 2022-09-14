/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:47:02 by junji             #+#    #+#             */
/*   Updhted: 2022/09/01 10:05:47 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define ERROR_MESSAGE "Error\n"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	size_t			idx;

	idx = -1;
	p = (unsigned char *)b;
	while (++idx < len)
		p[idx] = c;
	return (b);
}

size_t	ft_strlen(char *str)
{
	char	*init_pos;
	
	init_pos = str;
	while (*str)
		++str;
	return (str - init_pos);
}

void	ft_putstr(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (write(1, str, len) != len)
		exit(1);
}

void	put_error(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	write(2, str, len);
	exit(1);
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += (*str - '0');
		if ((sign > 0 && result == 214748364 && (*(str + 1) >= '8'))
			|| (sign < 0 && result == 214748364 && (*(str + 1) >= '9')))
			return (0);
		if (result > 214748364 && (*(str + 1) != 0))
			return (0);
		++str;
	}
	if (*str != 0)
		return (0);
	return (sign * result);
}

int	check_real_zero(char *str)
{
	if (*str == 0)
		return (0);
	if (*str == '-' || *str == '+')
		++str;
	while (*str == '0')
		++str;
	if (*str != 0)
		return (0);
	if (*(str - 1) != '0')
		return (0);
	return (1);
}

int	count_word(char *str)
{
	int	cnt;

	cnt = 0;
	if (*str == 0)
		return (1);
	while (*str)
	{
		while (*str && *str == ' ')
			++str;
		if (*str && *str != ' ')
		{
			++cnt;
			while (*str && *str != ' ')
				++str;
		}
	}
	return (cnt);
}

int	find_word_len(char *str)
{
	int	len;

	len = 0;
	while (*str && *str != ' ')
	{
		++len;
		++str;
	}
	return (len);
}

void	free_arr(char **copy, int idx)
{
	int	index;

	index = -1;
	while (++index < idx)
		free(copy[index]);
	free(copy);
}

char	**ft_split(char *str)
{
	char	**copy;
	int		idx;
	int		words;
	int		word_len;
	int		jdx;

	words = count_word(str);
	copy = malloc(sizeof(char *) * (words + 1));
	if (!copy)
		return (0);
	idx = -1;
	while (++idx < words)
	{
		while (*str && *str == ' ')
			++str;
		word_len = find_word_len(str);
		*(copy + idx) = malloc(sizeof(char) * (word_len + 1));
		if (*(copy + idx) == 0)
			free_arr(copy, idx);
		jdx = -1;
		while (*str && *str != ' ')
			(*(copy + idx))[++jdx] = *str++;
		(*(copy + idx))[++jdx] = 0;
	}
	*(copy + idx) = 0;
	return (copy);
}

typedef struct s_pivot_origin
{
	int dir;
	int pivot;
	int push_count;
	int	cnt;
} t_pivot_origin;

typedef struct s_node
{
	int data;
	int score;
	struct s_node *next;
}	t_node;

typedef struct s_pivot_node
{
	struct s_pivot_node *next;
	t_pivot_origin tool;
}	t_pivot_node;

typedef struct s_list
{
	t_node	*tail;
	int		cnt;
}	t_list;


typedef struct s_pivot_list
{
	t_pivot_node	*tail;
	int 	cnt;
}	t_pivot_list;


typedef struct s_pivot_new
{
	int pivot1;
	int pivot2;
	int p_count;
	int rb_count;
	int ra_count;
	int rrr_count;
	int alone;
	int flag;
} t_pivot_new;


void	init_list(t_list *list1, t_list *list2, t_list *list3, t_pivot_list *list4)
{
	ft_memset(list1, 0, sizeof(*list1));
	ft_memset(list2, 0, sizeof(*list2));
	ft_memset(list3, 0, sizeof(*list3));
	ft_memset(list4, 0, sizeof(*list4));
}

void	init_pivot_list(t_pivot_list *list)
{
	list->tail = NULL;
	list->cnt = 0;
}

int	insert_list(t_list *list, int number)
{
	t_node *new_node = malloc(sizeof(t_node));
	if (!new_node)
	{
		// free split;
		return (1);
	}
	new_node->data = number;
	if (list->tail == NULL)
	{
		list->tail = new_node;
		new_node->next = new_node;
	}
	else
	{
		new_node->next = list->tail->next;
		list->tail->next = new_node;
		list->tail = new_node;
	}
	++(list->cnt);
	return (0);
}

int	insert_pivot_list(t_pivot_list *list, int dir, int pivot, int push_count)
{
	t_pivot_node *new_node = malloc(sizeof(t_pivot_node));
	if (!new_node)
		return (1);
	new_node->tool.dir = dir;
	new_node->tool.pivot = pivot;
	new_node->tool.push_count = push_count;
	if (list->tail == NULL)
	{
		list->tail = new_node;
		new_node->next = new_node;
	}
	else
	{
		new_node->next = list->tail->next;
		list->tail->next = new_node;
		list->tail = new_node;
	}
	++(list->cnt);
	return (0);
}

int	insert_front_list(t_list *list, t_node *cur)
{
	if (list->tail == NULL)
	{
		list->tail = cur;
		cur->next = cur;
	}
	else
	{
		cur->next = list->tail->next;
		list->tail->next = cur;
	}
	++(list->cnt);
	return (0);
}

int	is_sorted(t_list *list)
{
	int cnt;
	t_node *cur;

	if (list->cnt <= 1)
		return (1);
	cnt = list->cnt;
	cur = list->tail->next;
	while (--cnt)
	{
		if (cur->data > cur->next->data)
			return (0);
		cur = cur->next;
	}
	return (1);
}

int	check_duplicate_number(t_list list)
{
	t_node *cur;
	t_node *tail;

	tail = list.tail;
	if (list.cnt <= 1)
		return (0);
	while (--list.cnt)
	{
		cur = list.tail->next;;
		while (cur != tail)
		{
			if (cur->data == list.tail->data)
				return (1);
			cur = cur->next;
		}
		list.tail = list.tail->next;
	}
	return (0);
}

int sa(t_list *list)
{
	t_node *tail_prev;
	t_node *temp;
	int cnt = 3;

	temp = list->tail->next;
	tail_prev = list->tail;
	if (list->cnt <= 1)
		return (0);
	while (--cnt >= 0)
		tail_prev = tail_prev->next;
	if (list->cnt == 2)
	{
		list->tail = list->tail->next;
		return 0;
	}
	else
	{
		list->tail->next = list->tail->next->next;
		list->tail->next->next = temp;
		temp->next = tail_prev;
		return (0);
	}
	return (0);
}

int sb(t_list *list)
{
	int	temp;
	t_node *cur;

	if (list->cnt <= 1)
		return (0);
	cur = list->tail->next;
	temp = cur->data;
	cur->data = cur->next->data;
	cur->next->data = temp;
	return (0);
}

int ss(t_list *list1, t_list *list2)
{
	sa(list1);
	sb(list2);
	return (0);
}

int pb(t_list *list1, t_list *list2)
{
	t_node *cur;

	if (list1->cnt <= 0)
		return (0);
	if (list1->cnt == 1)
	{
		cur = list1->tail;
		list1->tail = NULL;
		--(list2->cnt);
		insert_front_list(list2, cur);
		return (0);
	}
	cur = list1->tail->next;
	list1->tail->next = list1->tail->next->next;
	--(list1->cnt);
	insert_front_list(list2, cur);
	return (0);
}

int pa(t_list *list1, t_list *list2)
{
	t_node *cur;

	if (list2->cnt <= 0)
		return (0);
	if (list2->cnt == 1)
	{
		cur = list2->tail;
		list2->tail = NULL;
		--(list2->cnt);
		insert_front_list(list1, cur);
		return (0);
	}
	cur = list2->tail->next;
	list2->tail->next = list2->tail->next->next;
	--(list2->cnt);
	insert_front_list(list1, cur);
	return (0);
}

int	ra(t_list *list)
{
	if (list->cnt <= 1)
		return (0);
	list->tail = list->tail->next;
	return (0);
}

int rb(t_list *list)
{
	if (list->cnt <= 1)
		return (0);
	list->tail = list->tail->next;
	return (0);
}

int rr(t_list *list1, t_list *list2)
{
	ra(list1);
	rb(list2);
	return (0);
}

int rra(t_list *list)
{
	int cnt;

	cnt = list->cnt;
	if (list->cnt <= 1)
		return (0);
	while (--cnt)
		list->tail = list->tail->next;
	return (0);
}

int rrb(t_list *list)
{
	int cnt;

	cnt = list->cnt;
	if (list->cnt <= 1)
		return (0);
	while (--cnt)
		list->tail = list->tail->next;
	return (0);
}

int rrr(t_list *list1, t_list *list2)
{
	rra(list1);
	rrb(list2);
	return (0);
}

int	list_at(t_list *list, int left)
{
	t_node *first;

	if (list->cnt <= 0)
		return (0);
	first = list->tail->next;
	while (left--)
		first = first->next;
	return (first->data);
}

int	list_at_score(t_list *list, int left)
{
	t_node *first;

	if (list->cnt <= 0)
		return (0);
	first = list->tail->next;
	while (left--)
		first = first->next;
	return (first->score);
}

int ft_swap(t_list *list, int left, int right)
{
	int	temp;
	t_node *first;
	t_node *second;

	if (list->cnt <= 1)
		return (1);
	first = list->tail->next;
	second = list->tail->next;
	while (left--)
		first = first->next;
	temp = first->data;
	while (right--)
		second = second->next;
	first->data = second->data;
	second->data = temp;
	return (0);
}

void quick_sort(t_list *list, int start, int end)
{
	int pivot = start;
	int left = start + 1;
	int right = end;
	if (start >= end)
		return ;
	while (left <= right)
	{
		while (left <= end && list_at(list, left) <= list_at(list, pivot))
			++left;
		while (right > start && list_at(list, right) >= list_at(list, pivot))
			--right;
		if (left > right)
			ft_swap(list, pivot, right);
		else
			ft_swap(list, left, right);
	}
	quick_sort(list, start, right - 1);
	quick_sort(list, right + 1, end);
}

void	mark_rank(t_list *temp, t_list *list)
{
	int		score;
	int		temp_cnt;
	int		list_cnt;
	t_node	*cur;
	t_node	*temp_cur;

	if (list->cnt <= 0)
		return ;
	score = 1;
	temp_cur = temp->tail->next; 
	cur = list->tail->next;
	temp_cnt = temp->cnt;
	list_cnt = list->cnt;
	while (temp_cnt--)
	{
		list_cnt = list->cnt;
		cur = list->tail->next;
		while (list_cnt--)
		{
			if (cur->data == temp_cur->data)
				cur->score = score++;
			cur = cur->next;
		}
		temp_cur = temp_cur->next;
	}
}

void	compare_two_sort_list(t_list *list1, t_list *list2, int flag)
{
	int score1 = list_at_score(list2, 0);
	int score2 = list_at_score(list2, 1);

	int score3 = list_at_score(list1, 0);
	int score4 = list_at_score(list1, 1);
	if (flag == 0)
	{
			if (score3 > score4)
			{
				ft_putstr("sa\n");
				sa(list1);
			}
	}
	else
	{
		if (list2->cnt == 2)
		{
			if (score1 < score2)
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
		{
			if (score1 < score2)
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
	}
}
void	delete_all_stack(t_list **list)
{
	t_node *temp;
	t_node *tail_prev;
	int			cnt;

	if ((*list)->cnt <= 0)
		return ;
	while ((*list)->cnt > 0)
	{
		if ((*list)->cnt == 1)
		{
			--((*list)->cnt);
			free((*list)->tail);
			(*list)->tail = NULL;
		}
		else
		{
			cnt = (*list)->cnt;
			temp = (*list)->tail;
			tail_prev = (*list)->tail;
			while (--cnt)
				tail_prev = tail_prev->next;
			tail_prev->next = (*list)->tail->next;
			(*list)->tail = tail_prev;
			free(temp);
			temp = NULL;
			--((*list)->cnt);
		}
	}
}

void	delete_pivot_node(t_pivot_list **pivot_list)
{
	t_pivot_node *temp;
	t_pivot_node *tail_prev;
	int			cnt;

	cnt = (*pivot_list)->cnt;
	if (cnt <= 0)
		return ;
	if (cnt == 1)
	{
		--((*pivot_list)->cnt);
		free((*pivot_list)->tail);
		(*pivot_list)->tail = NULL;
	}
	else
	{
		temp = (*pivot_list)->tail;
		tail_prev = (*pivot_list)->tail;
		while (--cnt)
			tail_prev = tail_prev->next;
		tail_prev->next = (*pivot_list)->tail->next;
		(*pivot_list)->tail = tail_prev;
		free(temp);
		temp = NULL;
		--((*pivot_list)->cnt);
	}
}


void	compare_three_sort_list(t_list *list1, t_list *list2, int flag)
{
	int score4 = list_at_score(list2, 0);
	int score5 = list_at_score(list2, 1);
	int score6 = list_at_score(list2, 2);

	int score1 = list_at_score(list1, 0);
	int score2 = list_at_score(list1, 1);
	int score3 = list_at_score(list1, 2);
	if (flag == 0)
	{
		if (list1->cnt == 3)
		{
			if (score1 > score2 && score2 > score3)
			{
				ra(list1);
				sa(list1);
				ft_putstr("ra\n");
				ft_putstr("sa\n");
			}
			else if (score1 > score2 && score1 > score3 && score2 < score3)
			{
				ra(list1);
				ft_putstr("ra\n");
			}
			else if (score2 > score1 && score2 > score3 && score1 > score3)
			{
				rra(list1);
				ft_putstr("rra\n");
			}
			else if (score2 > score1 && score2 > score3 && score3 > score1)
			{
				rra(list1);
				sa(list1);
				ft_putstr("rra\n");
				ft_putstr("sa\n");
			}
			else if (score3 > score1 && score3 > score2 && score1 > score2)
			{
				sa(list1);
				ft_putstr("sa\n");
			}
		}
		else
		{
			if (score1 > score2 && score2 > score3)
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
			else if (score1 > score2 && score1 > score3 && score2 < score3)
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
			else if (score2 > score1 && score2 > score3 && score1 > score3)
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
			else if (score2 > score1 && score2 > score3 && score3 > score1)
			{
				ra(list1);
				sa(list1);
				rra(list1);
				ft_putstr("ra\n");
				ft_putstr("sa\n");
				ft_putstr("rra\n");
			}
			else if (score3 > score1 && score3 > score2 && score1 > score2)
			{
				sa(list1);
				ft_putstr("sa\n");
			}
		}
	}
	else
	{
		if (list2->cnt == 3)
		{
			if (score4 > score5 && score5 > score6)
			{
				pa(list1, list2);
				pa(list1, list2);
				pa(list1, list2);
				ft_putstr("pa\n");
				ft_putstr("pa\n");
				ft_putstr("pa\n");
			}
			else if (score4 > score5 && score4 > score6 && score5 < score6)
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
			else if (score5 > score4 && score5 > score6 && score4 > score6)
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
			else if (score5 > score4 && score5 > score6 && score6 > score4)
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
			else if (score6 > score4 && score6 > score5 && score4 > score5)
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
			else
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
		else
		{
			if (score4 > score5 && score5 > score6)
			{
				pa(list1, list2);
				pa(list1, list2);
				pa(list1, list2);
				ft_putstr("pa\n");
				ft_putstr("pa\n");
				ft_putstr("pa\n");
			}
			else if (score4 > score5 && score4 > score6 && score5 < score6)
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
			else if (score5 > score4 && score5 > score6 && score4 > score6)
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
			else if (score5 > score4 && score5 > score6 && score6 > score4)
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
			else if (score6 > score4 && score6 > score5 && score4 > score5)
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
			else
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
	}
}

void	sort_list(t_list *list1, t_list *list2, int dir, int count)
{
	if (count == 3)
	{
		if (dir == 0)
			compare_three_sort_list(list1, list2, 0);
		else
			compare_three_sort_list(list1, list2, 1);
	}
	else if (count == 2)
	{
		if (dir == 0)
			compare_two_sort_list(list1, list2, 0);
		else
			compare_two_sort_list(list1, list2, 1);
	}
	else if (count == 1)
	{
		if (dir == 1)
		{
			pa(list1, list2);
			ft_putstr("pa\n");
		}
	}
}

void	init_pivot_new(t_pivot_new	*tool2)
{
	tool2->pivot1 = 0;
	tool2->pivot2 = 0;
	tool2->p_count = 0;
	tool2->ra_count = 0;
	tool2->rb_count = 0;
	tool2->rrr_count = 0;
	tool2->alone = 0;
	tool2->flag = 0;
}

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
	int ra_count;
	int rb_count;

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
	int ra_count;
	int rb_count;


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

void	use_one_pivot_a_to_b_2(t_list *list1, t_list *list2, t_pivot_origin *pivot_origin, t_pivot_new *pivot_new)
{
	if (!(pivot_new->alone))
	{
		while (--(pivot_new->ra_count) >= 0)
		{
			rra(list1);
			ft_putstr("rra\n");
		}
	}
}

void	use_one_pivot_a_to_b(t_list *list1, t_list *list2, t_pivot_origin *pivot_origin, t_pivot_new *pivot_new)
{
	int	cnt;

	cnt = pivot_origin->push_count;
	if (pivot_origin->push_count == list1->cnt)
		pivot_new->alone = 1;
	pivot_new->pivot1 = pivot_origin->pivot - pivot_origin->push_count / 2;
	while (--cnt >= 0)
	{
		if (list_at_score(list1, 0) <= pivot_new->pivot1)
		{
			pb(list1, list2);
			ft_putstr("pb\n");
			++(pivot_new->p_count);
		}
		else
		{
			ra(list1);
			ft_putstr("ra\n");
			++(pivot_new->ra_count);
		}
	}
	use_one_pivot_a_to_b_2(list1, list2, pivot_origin, pivot_new);
}

void	use_two_pivot_a_to_b_2(t_list *list1, t_list *list2, t_pivot_origin *pivot_origin, t_pivot_new *pivot_new)
{
	if (pivot_new->ra_count <= pivot_new->rb_count)
		rotate_b(list1, list2, pivot_new);
	else
		rotate_a(list1, list2, pivot_new);
}

void	find_two_pivot_alone(t_list *list, t_pivot_origin *old_pivot, t_pivot_new *new_pivot) 
{
		new_pivot->pivot1 = old_pivot->pivot - old_pivot->push_count / 3;
		new_pivot->pivot2 = old_pivot->pivot - old_pivot->push_count / 3 * 2;
		if (list->cnt == old_pivot->push_count)
			new_pivot->alone = 1;
}

void	use_two_pivot_a_to_b(t_list *list1, t_list *list2, t_pivot_origin *pivot_origin, t_pivot_new *pivot_new)
{
	find_two_pivot_alone(list1, pivot_origin, pivot_new);
	pivot_origin->cnt = pivot_origin->push_count;
	while (--(pivot_origin->cnt) >= 0)
	{
		if (list_at_score(list1, 0) <= pivot_new->pivot1)
		{
			pb(list1, list2);
			++pivot_new->p_count;
			ft_putstr("pb\n");
			if (list_at_score(list2, 0) > pivot_new->pivot2)
			{
				rb(list2);
				ft_putstr("rb\n");
				++pivot_new->rb_count;
			}
		}
		else
		{
			ra(list1);
			++pivot_new->ra_count;
			ft_putstr("ra\n");
		}
	}
	use_two_pivot_a_to_b_2(list1, list2, pivot_origin, pivot_new);
}

int		push_a_to_b_2(t_pivot_list **pivot_list, t_pivot_origin *old_pivot, t_pivot_new *new_pivot)
{
	if (insert_pivot_list(*pivot_list, 1, new_pivot->pivot2, new_pivot->p_count - new_pivot->rb_count) == 1)
		return (1);
	if (insert_pivot_list(*pivot_list, 1, new_pivot->pivot1, new_pivot->rb_count))
		return (1);
	if (insert_pivot_list(*pivot_list, 0, old_pivot->pivot, old_pivot->push_count - new_pivot->p_count) == 1)
		return (1);
	return (0);
}

int	insert_pivot_list_a_to_b_6(t_pivot_list **pivot_list, t_pivot_origin *old_pivot, t_pivot_new *new_pivot)
{
	if (insert_pivot_list(*pivot_list, 1, new_pivot->pivot1, new_pivot->p_count) == 1)
		return (1);
	if (insert_pivot_list(*pivot_list, 0, old_pivot->pivot, old_pivot->push_count - new_pivot->p_count) == 1)
		return (1);
	return (0);
}

int		push_a_to_b(t_list *list1, t_list *list2, t_pivot_list **pivot_list)
{
	t_pivot_origin		old_pivot;
	t_pivot_new			new_pivot;

	old_pivot = (*pivot_list)->tail->tool;
	if (old_pivot.push_count <= 3)
	{
		sort_list(list1, list2, old_pivot.dir, old_pivot.push_count);
		delete_pivot_node(pivot_list);
		return (0);
	}
	memset(&new_pivot, 0, sizeof(new_pivot));
	delete_pivot_node(pivot_list);
	if (old_pivot.push_count <= 6)
	{
		use_one_pivot_a_to_b(list1, list2, &old_pivot, &new_pivot);
		if (insert_pivot_list_a_to_b_6(pivot_list, &old_pivot, &new_pivot) == 1)
			return (1);
	}
	else
	{
		use_two_pivot_a_to_b(list1, list2, &old_pivot, &new_pivot);
		if (push_a_to_b_2(pivot_list, &old_pivot, &new_pivot) == 1)
			return (1);
	}
	return (0);
}

void	use_one_pivot_b_to_a_2(t_list *list1, t_list *list2, t_pivot_origin *pivot_origin, t_pivot_new *pivot_new)
{
	if (!(pivot_new->alone))
	{
		while (--(pivot_new->rb_count) >= 0)
		{
			rrb(list2);
			ft_putstr("rrb\n");
		}
	}
}

void	use_one_pivot_b_to_a(t_list *list1, t_list *list2, t_pivot_origin *pivot_origin, t_pivot_new *pivot_new)
{
	int	cnt;

	cnt = pivot_origin->push_count;
	if (pivot_origin->push_count == list2->cnt)
		pivot_new->alone = 1;
	pivot_new->pivot1 = pivot_origin->pivot - pivot_origin->push_count / 2;
	while (--cnt >= 0)
	{
		if (list_at_score(list2, 0) > pivot_new->pivot1)
		{
			pa(list1, list2);
			ft_putstr("pa\n");
			++(pivot_new->p_count);
		}
		else
		{
			rb(list2);
			ft_putstr("rb\n");
			++(pivot_new->rb_count);
		}
	}
	use_one_pivot_b_to_a_2(list1, list2, pivot_origin, pivot_new);
}

int	insert_pivot_list_b_to_a_6(t_pivot_list **pivot_list, t_pivot_origin *old_pivot, t_pivot_new *new_pivot)
{
	if (insert_pivot_list(*pivot_list, 1, new_pivot->pivot1, old_pivot->push_count - new_pivot->p_count) == 1)
		return (1);
	if (insert_pivot_list(*pivot_list, 0, old_pivot->pivot, new_pivot->p_count) == 1)
		return (1);
	return (0);
}

void	use_two_pivot_b_to_a_2(t_list *list1, t_list *list2, t_pivot_origin *pivot_origin, t_pivot_new *pivot_new)
{
	if (pivot_new->ra_count <= pivot_new->rb_count)
		rotate_b(list1, list2, pivot_new);
	else
		rotate_a(list1, list2, pivot_new);
}

void	use_two_pivot_b_to_a(t_list *list1, t_list *list2, t_pivot_origin *pivot_origin, t_pivot_new *pivot_new)
{
	find_two_pivot_alone(list1, pivot_origin, pivot_new);
	pivot_origin->cnt = pivot_origin->push_count;
	while (--(pivot_origin->cnt) >= 0)
	{
		if (list_at_score(list2, 0) > pivot_new->pivot2)
		{
			pa(list1, list2);
			++pivot_new->p_count;
			ft_putstr("pa\n");
			if (list_at_score(list1, 0) > pivot_new->pivot1 && list1->cnt > 1) // list1->cnt > 1
			{
				ra(list1);
				ft_putstr("ra\n");
				++pivot_new->ra_count;
			}
		}
		else
		{
			rb(list2);
			++pivot_new->rb_count;
			ft_putstr("rb\n");
		}
	}
//	use_two_pivot_b_to_a_2(list1, list2, pivot_origin, pivot_new);
}

int		push_b_to_a_2(t_pivot_list **pivot_list, t_pivot_origin *old_pivot, t_pivot_new *new_pivot)
{
	if (insert_pivot_list(*pivot_list, 1, new_pivot->pivot2, new_pivot->rb_count) == 1)
		return (1);
	if (insert_pivot_list(*pivot_list, 0, new_pivot->pivot1, new_pivot->ra_count) == 1)
		return (1);
	if (insert_pivot_list(*pivot_list, 2, new_pivot->ra_count, new_pivot->rb_count) == 1)
		return (1);
	if (insert_pivot_list(*pivot_list, 0, old_pivot->pivot, new_pivot->p_count - new_pivot->ra_count) == 1)
		return (1);
	return (0);
}

int	push_b_to_a(t_list *list1, t_list *list2, t_pivot_list **pivot_list)
{
	t_pivot_origin		old_pivot;
	t_pivot_new			new_pivot;

	old_pivot = (*pivot_list)->tail->tool;
	if (old_pivot.push_count <= 3)
	{
		sort_list(list1, list2, old_pivot.dir, old_pivot.push_count);
		delete_pivot_node(pivot_list);
		return (0);
	}
	memset(&new_pivot, 0, sizeof(new_pivot));
	delete_pivot_node(pivot_list);
	if (old_pivot.push_count <= 6)
	{
		use_one_pivot_b_to_a(list1, list2, &old_pivot, &new_pivot);
		if (insert_pivot_list_b_to_a_6(pivot_list, &old_pivot, &new_pivot) == 1)
			return (1);
	}
	else
	{
		use_two_pivot_b_to_a(list1, list2, &old_pivot, &new_pivot);
		if (push_b_to_a_2(pivot_list, &old_pivot, &new_pivot) == 1)
			return (1);
	}
	return (0);
}

int	push_stack_a(t_list *list1, t_list *list2, t_pivot_list **pivot_list)
{
	t_pivot_origin	tool;
	t_pivot_new	tool2;
	t_pivot_new	tool3;
	int		cnt;

	tool = (*pivot_list)->tail->tool;
	if (tool.push_count <= 3)
	{
		sort_list(list1, list2, tool.dir, tool.push_count);
		delete_pivot_node(pivot_list);
		return	(0);
	}
	init_pivot_new(&tool2);
	delete_pivot_node(pivot_list);
	cnt = tool.push_count;
	if (tool.push_count == list2->cnt)
		tool2.alone = 1;
	if (tool.push_count <= 6)
	{
		tool2.pivot1 = tool.pivot - tool.push_count / 2;
		while (--cnt >= 0)
		{
			if (list_at_score(list2, 0) > tool2.pivot1)
			{
				pa(list1, list2);
				++tool2.p_count;
				ft_putstr("pa\n");
			}
			else
			{
				rb(list2);
				++tool2.rb_count;
				ft_putstr("rb\n");
			}
		}
		if (!(tool2.alone))
		{
			while (--tool2.rb_count >= 0)
			{
				rrb(list2);
				ft_putstr("rrb\n");
			}
		}
		tool3 = tool2;
		if (insert_pivot_list(*pivot_list, 1, tool3.pivot1, tool.push_count - tool3.p_count) == 1)
			return (1);
		if (insert_pivot_list(*pivot_list, 0, tool.pivot, tool3.p_count) == 1)
			return (1);
	}
	else
	{

		tool2.pivot1 = tool.pivot - tool.push_count / 3;
		tool2.pivot2 = tool.pivot - tool.push_count / 3 * 2;
		while (--tool.push_count >= 0)
		{
			if (list_at_score(list2, 0) > tool2.pivot2)
			{
				pa(list1, list2);
				++tool2.p_count;
				ft_putstr("pa\n");
				if (list_at_score(list1, 0) <= tool2.pivot1 && list1->cnt > 1)
				{
					ra(list1);
					ft_putstr("ra\n");
					++tool2.ra_count;
				}
			}
			else
			{
				rb(list2);
				++tool2.rb_count;
				ft_putstr("rb\n");
			}
		}
		if (insert_pivot_list(*pivot_list, 1, tool2.pivot2, tool2.rb_count) == 1)
			return (1);
		if (insert_pivot_list(*pivot_list, 0, tool2.pivot1, tool2.ra_count) == 1)
			return (1);
		if (insert_pivot_list(*pivot_list, 2, tool2.ra_count, tool2.rb_count) == 1)
			return (1);
		if (insert_pivot_list(*pivot_list, 0, tool.pivot, tool2.p_count - tool2.ra_count) == 1)
			return (1);
	}
	return (0);
}

void	rotate_stack(t_list *list1, t_list *list2, t_pivot_list **pivot_list)
{
	t_pivot_origin	tool;
	int				ra_count;
	int				rb_count;
	int				rrr_count;

	tool = (*pivot_list)->tail->tool;
	ra_count = tool.pivot;
	rb_count = tool.push_count;
	if (ra_count <= rb_count)
		rotate_stack_b(list1, list2, ra_count, rb_count);
	else if (ra_count > rb_count)
		rotate_stack_a(list1, list2, ra_count, rb_count);
	delete_pivot_node(pivot_list);
}

#include <stdio.h>
void	iterate_pivot_list(t_pivot_list list)
{
	t_pivot_node *cur;

	if (list.cnt == 0)
		return ;
	cur = list.tail->next;
	if (list.cnt == 1)
	{
		printf("dir: %d\n", cur->tool.dir);
		printf("pivot: %d\n", cur->tool.pivot);
		printf("push_count: %d\n", cur->tool.push_count);
	}
	else
	{
		while (list.cnt--)
		{
			printf("dir: %d\n", cur->tool.dir);
			printf("pivot: %d\n", cur->tool.pivot);
			printf("push_count: %d\n", cur->tool.push_count);
			cur = cur->next;
		}
	}
}

void	iterate_list(t_list list)
{
	t_node *cur;

	if (list.cnt == 0)
		return ;
	cur = list.tail->next;
	if (list.cnt == 1)
		printf("%d\n", cur->data);
	else
	{
		while (list.cnt--)
		{
			printf("cur->data:%d\n", cur->data);
			printf("score:%d\n", cur->score);
			cur = cur->next;
		}
		printf("\n");
	}
}

int	recur(t_list *list1, t_list *list2, t_pivot_list *pivot_list)
{
	t_pivot_node *cur;

	while (pivot_list->cnt > 0)
	{
		iterate_pivot_list(*pivot_list);
		iterate_list(*list1);
		iterate_list(*list2);
		//sleep(2);
		if (is_sorted(list1) == 1 && list2->cnt == 0)
			break ;
		cur = pivot_list->tail;
		if (cur->tool.dir == 0)
		{
			if (push_a_to_b(list1, list2, &pivot_list) == 1)
				return (1);
		}
		else if (cur->tool.dir == 1)
		{
			if (push_b_to_a(list1, list2, &pivot_list) == 1)
				return (1);
		}
		else if (cur->tool.dir == 2)
		{
			rotate_stack(list1, list2, &pivot_list);
		}
	}
	delete_pivot_node(&pivot_list);
	return (0);
}

typedef struct s_info_input
{
	int		i;
	int		j;
	int		element_cnt;
	int		number;
	char	**element;
} t_info_input;


int		check_valid_input(int argc, char *argv[], t_list *temp, t_list *stack_a)
{
	t_info_input	input;

	ft_memset(&input, 0, sizeof(input));
	while (++input.i < argc)
	{
		input.element_cnt = count_word(argv[input.i]);
		input.element = ft_split(argv[input.i]);
		input.j = -1;
		while (++input.j < input.element_cnt)
		{
			input.number = ft_atoi(input.element[input.j]);
			if (input.number == 0 && !check_real_zero(input.element[input.j]))
				return (1);
			else
			{
				if (insert_list(temp, input.number) == 1 || insert_list(stack_a, input.number) == 1)
					return (1);
			}
		}
		free_arr(input.element, input.element_cnt);
	}
	return (0);
}

int	check_duplicate_list(t_list list)
{
	t_node *cur;
	t_node *tail;

	tail = list.tail;
	if (list.cnt <= 1)
		return (0);
	while (--list.cnt)
	{
		cur = list.tail->next;;
		while (cur != tail)
		{
			if (cur->data == list.tail->data)
				return (1);
			cur = cur->next;
		}
		list.tail = list.tail->next;
	}
	return (0);
}

int	rank_score(t_list *sorted_stack, t_list *stack_a, t_pivot_list *pivot_list)
{
	quick_sort(sorted_stack, 0, sorted_stack->cnt - 1);
	mark_rank(sorted_stack, stack_a);
	if (insert_pivot_list(pivot_list, 0, stack_a->cnt, stack_a->cnt) == 1)
		return (1);
	return (0);
}

void	free_stack(t_list *list1, t_list *list2)
{
	delete_all_stack(&list1);
	delete_all_stack(&list2);
}

int	main(int argc, char *argv[])
{
	t_list			stack_a;
	t_list			stack_b;
	t_list			sorted_stack;
	t_pivot_list	pivot_list;
	
	init_list(&stack_a, &stack_b, &sorted_stack, &pivot_list);
	if (check_valid_input(argc, argv, &sorted_stack, &stack_a) == 1)
		put_error(ERROR_MESSAGE);
	if (check_duplicate_list(stack_a) == 1)
		put_error(ERROR_MESSAGE);
	if (rank_score(&sorted_stack, &stack_a, &pivot_list) == 1)
		put_error(ERROR_MESSAGE);
	if (recur(&stack_a, &stack_b, &pivot_list) == 1)
		put_error(ERROR_MESSAGE);
	free_stack(&stack_a, &sorted_stack);
	return (0);
}
