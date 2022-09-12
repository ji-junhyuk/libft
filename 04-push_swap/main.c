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
	write(2, str, len);
}
int command_cnt;
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
	if (*str == '\0')
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
//		copy[idx] = malloc(sizeof(char) * (word_len + 1));
//		if (!copy[idx])
//			free_arr(copy, idx);
//		jdx = -1;
//		while (*str && *str != ' ')
//			copy[idx][++jdx] = *str++;
//		copy[idx][++jdx] = 0;
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

typedef struct s_tool
{
	int dir;
	int pivot;
	int push_count;
//	int stack_a_cnt;
//	int stack_b_cnt;
//	int stack_a_pivot;
//	int stack_b_pivot;
} t_tool;

typedef struct s_node
{
	int data;
	int score;
	struct s_node *next;
}	t_node;

typedef struct s_pivot_node
{
	struct s_pivot_node *next;
	t_tool tool;
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


typedef struct s_tool2
{
	int pivot1;
	int pivot2;
	int p_count;
	int rb_count;
	int ra_count;
	int rrr_count;
	int alone;
	int flag;
} t_tool2;

void	init_list(t_list *list)
{
	list->tail = NULL;
	list->cnt = 0;
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
	{
		exit(1);
		return (1);
	}
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
				++command_cnt;
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
				command_cnt += 3;
			}
			else
			{
				pa(list1, list2);
				pa(list1, list2);
				ft_putstr("pa\n");
				ft_putstr("pa\n");
				command_cnt += 2;
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
				command_cnt += 4;
			}
			else
			{
				pa(list1, list2);
				pa(list1, list2);
				ft_putstr("pa\n");
				ft_putstr("pa\n");
				command_cnt += 2;
			}
		}
	}
}
void	delete_stack(t_list **list)
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
				command_cnt += 2;
			}
			else if (score1 > score2 && score1 > score3 && score2 < score3)
			{
				ra(list1);
				ft_putstr("ra\n");
				++command_cnt;
			}
			else if (score2 > score1 && score2 > score3 && score1 > score3)
			{
				rra(list1);
				ft_putstr("rra\n");
				++command_cnt;
			}
			else if (score2 > score1 && score2 > score3 && score3 > score1)
			{
				rra(list1);
				sa(list1);
				ft_putstr("rra\n");
				ft_putstr("sa\n");
				command_cnt += 2;
			}
			else if (score3 > score1 && score3 > score2 && score1 > score2)
			{
				sa(list1);
				ft_putstr("sa\n");
				++command_cnt;
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
				command_cnt += 7;
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
				command_cnt += 4;
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
				command_cnt += 4;
			}
			else if (score2 > score1 && score2 > score3 && score3 > score1)
			{
				ra(list1);
				sa(list1);
				rra(list1);
				ft_putstr("ra\n");
				ft_putstr("sa\n");
				ft_putstr("rra\n");
				command_cnt += 3;
			}
			else if (score3 > score1 && score3 > score2 && score1 > score2)
			{
				sa(list1);
				ft_putstr("sa\n");
				++command_cnt;
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
				command_cnt += 3;
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
				command_cnt += 4;
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
				command_cnt += 4;
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
				command_cnt += 4;
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
				command_cnt += 4;
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
				command_cnt += 5;
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
				command_cnt += 3;
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
				command_cnt += 4;
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
				command_cnt += 4;
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
				command_cnt += 5;
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
				command_cnt += 6;
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
				command_cnt += 6;
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
			++command_cnt;
		}
	}
}

void	init_tool2(t_tool2	*tool2)
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

void	push_stack_b(t_list *list1, t_list *list2, t_pivot_list **pivot_list)
{
	t_tool	tool;
	t_tool2	tool2;
	t_tool2 tool3;
	int		cnt;

	tool = (*pivot_list)->tail->tool;
	if (tool.push_count <= 3)
	{
		sort_list(list1, list2, tool.dir, tool.push_count);
		delete_pivot_node(pivot_list);
		return ;
	}
	init_tool2(&tool2);
	cnt = tool.push_count;
	delete_pivot_node(pivot_list);
	if (tool.push_count == list1->cnt)
		tool2.alone = 1;
	if (tool.push_count <= 6)
	{		
		tool2.pivot1 = tool.pivot - tool.push_count / 2;
		while (--cnt >= 0)
		{
			if (list_at_score(list1, 0) <= tool2.pivot1)
			{
				pb(list1, list2);
				ft_putstr("pb\n");
				++tool2.p_count;
				++command_cnt;
			}
			else
			{
				ra(list1);
				ft_putstr("ra\n");
				++tool2.ra_count;
				++command_cnt;
			}
		}
		if (!(tool2.alone))
		{
			while (--tool2.ra_count >= 0)
			{
				rra(list1);
				ft_putstr("rra\n");
				++command_cnt;
			}
		}
		insert_pivot_list(*pivot_list, 1, tool2.pivot1, tool2.p_count);
		insert_pivot_list(*pivot_list, 0, tool.pivot, tool.push_count - tool2.p_count);
	}
	else
	{
		tool2.pivot1 = tool.pivot - tool.push_count / 3;
		tool2.pivot2 = tool.pivot - tool.push_count / 3 * 2;
		while (--cnt >= 0)
		{
			if (list_at_score(list1, 0) <= tool2.pivot1)
			{
				pb(list1, list2);
				++tool2.p_count;
				++command_cnt;
				ft_putstr("pb\n");
				if (list_at_score(list2, 0) > tool2.pivot2)
				{
					rb(list2);
					ft_putstr("rb\n");
					++tool2.rb_count;
					++command_cnt;
				}
			}
			else
			{
				ra(list1);
				++tool2.ra_count;
				ft_putstr("ra\n");
				++command_cnt;
			}
		}
		tool3 = tool2;
		if (tool2.ra_count <= tool2.rb_count)
		{
			tool2.rrr_count = tool2.ra_count;
			while (--tool2.rrr_count >= 0)
			{
				rrr(list1, list2);
				ft_putstr("rrr\n");
				++command_cnt;
			}
			tool2.rb_count -= tool2.ra_count;
			while (--tool2.rb_count >= 0)
			{
				rrb(list2);
				ft_putstr("rrb\n");
				++command_cnt;
			}
		}
		else if (tool2.ra_count > tool2.rb_count)
		{
			tool2.rrr_count = tool2.rb_count;
			while (--tool2.rrr_count >= 0)
			{
				rrr(list1, list2);
				ft_putstr("rrr\n");
				++command_cnt;
			}
			tool2.ra_count -= tool2.rb_count;
			while (tool2.alone == 0 && --tool2.ra_count >= 0)
			{
				rra(list1);
				ft_putstr("rra\n");
				++command_cnt;
			}
		}
		insert_pivot_list(*pivot_list, 1, tool3.pivot2, tool3.p_count - tool3.rb_count);
		insert_pivot_list(*pivot_list, 1, tool3.pivot1, tool3.rb_count);
		insert_pivot_list(*pivot_list, 0, tool.pivot, tool.push_count - tool3.p_count);
	}
}

void	push_stack_a(t_list *list1, t_list *list2, t_pivot_list **pivot_list)
{
	t_tool	tool;
	t_tool2	tool2;
	int		cnt;

	tool = (*pivot_list)->tail->tool;
	if (tool.push_count <= 3)
	{
		sort_list(list1, list2, tool.dir, tool.push_count);
		delete_pivot_node(pivot_list);
		return ;
	}
	init_tool2(&tool2);
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
				++command_cnt;
			}
			else
			{
				rb(list2);
				++tool2.rb_count;
				ft_putstr("rb\n");
				++command_cnt;
			}
		}
		if (!(tool2.alone))
		{
			while (--tool2.rb_count >= 0)
			{
				rrb(list2);
				ft_putstr("rrb\n");
				++command_cnt;
			}
		}
		insert_pivot_list(*pivot_list, 1, tool2.pivot1, tool.push_count - tool2.p_count);
		insert_pivot_list(*pivot_list, 0, tool.pivot, tool2.p_count);
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
				++command_cnt;
				if (list_at_score(list1, 0) <= tool2.pivot1 && list1->cnt > 1)
				{
					ra(list1);
					ft_putstr("ra\n");
					++tool2.ra_count;
					++command_cnt;
				}
			}
			else
			{
				rb(list2);
				++tool2.rb_count;
				ft_putstr("rb\n");
				++command_cnt;
			}
		}
		insert_pivot_list(*pivot_list, 1, tool2.pivot2, tool2.rb_count);
		insert_pivot_list(*pivot_list, 0, tool2.pivot1, tool2.ra_count);
		insert_pivot_list(*pivot_list, 2, tool2.ra_count, tool2.rb_count);
		insert_pivot_list(*pivot_list, 0, tool.pivot, tool2.p_count - tool2.ra_count);
	}
}

void	rotate_stack(t_list *list1, t_list *list2, t_pivot_list **pivot_list)
{
	t_tool tool;

	tool = (*pivot_list)->tail->tool;
	int	ra_count = tool.pivot;
	int rb_count = tool.push_count;
	int	rrr_count;
	if (ra_count <= rb_count)
	{
		rrr_count = ra_count;
		while (--rrr_count >= 0)
		{
			rrr(list1, list2);
			ft_putstr("rrr\n");
			++command_cnt;
		}
		rb_count -= ra_count;
		while (--rb_count >= 0)
		{
			rrb(list2);
			ft_putstr("rrb\n");
			++command_cnt;
		}
	}
	else if (ra_count > rb_count)
	{
		rrr_count = rb_count;
		while (--rrr_count >= 0)
		{
			rrr(list1, list2);
			ft_putstr("rrr\n");
			++command_cnt;
		}
		ra_count -= rb_count;
		while (--ra_count >= 0)
		{
			rra(list1);
			ft_putstr("rra\n");
			++command_cnt;
		}
	}
	delete_pivot_node(pivot_list);
}

void	recur(t_list *list1, t_list *list2, t_pivot_list *pivot_list)
{
	t_pivot_node *cur;

	while (pivot_list->cnt > 0)
	{
		if (is_sorted(list1) == 1 && list2->cnt == 0)
			break ;
		cur = pivot_list->tail;
		if (cur->tool.dir == 0)
			push_stack_b(list1, list2, &pivot_list);
		else if (cur->tool.dir == 1)
			push_stack_a(list1, list2, &pivot_list);
		else if (cur->tool.dir == 2)
			rotate_stack(list1, list2, &pivot_list);
	}
	delete_pivot_node(&pivot_list);
}

#include <stdio.h>
int	main(int argc, char *argv[])
{
	int		i;
	int		j; 
	int		number;
	int		element_cnt;
	int		total_cnt;
	char	**element;

	t_list			stack_a;
	t_list			stack_b;
	t_list			temp;
	t_pivot_list	pivot_list;
	t_list			*stack_a_pointer;
	t_list			*temp_pointer;

	stack_a_pointer = &stack_a;
	temp_pointer = &temp;
	init_list(&stack_a);
	init_list(&stack_b);
	init_list(&temp);
	init_pivot_list(&pivot_list);
	element_cnt = 0;
	element = NULL;
	total_cnt = 0;
	i = 0;
	while (++i < argc)
	{
		element_cnt = count_word(argv[i]);
		element = ft_split(argv[i]);
		total_cnt += element_cnt;
		j = -1;
		while (++j < element_cnt)
		{
			number = ft_atoi(element[j]);
			if (number == 0 && !check_real_zero(element[j]))
			{
				ft_putstr("Error\n");
				exit(1);
			}
			else
			{
				if (insert_list(&temp, number) == 1 || insert_list(&stack_a, number) == 1)
				{
					ft_putstr("Error\n");
					exit(1);
				}
			}
		}
		free_arr(element, element_cnt);
	}
	if (check_duplicate_number(stack_a) == 1)
	{
		ft_putstr("Error\n");
		exit(1);
	}
	quick_sort(&temp, 0, temp.cnt - 1);
	mark_rank(&temp, &stack_a);
	insert_pivot_list(&pivot_list, 0, stack_a.cnt, stack_a.cnt);
	recur(&stack_a, &stack_b, &pivot_list);
	delete_stack(&stack_a_pointer);
	delete_stack(&temp_pointer);
	return (0);
}
