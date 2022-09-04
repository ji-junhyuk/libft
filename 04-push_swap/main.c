/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 13:40:33 by junji             #+#    #+#             */
/*   Updated: 2022/09/04 15:55:37 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
	if (*str == '-' || *str == '+')
		++str;
	while (*str == '0')
		++str;
	if (*str != 0)
		return (0);
	return (1);
}

int	count_word(char *str)
{
	int	cnt;

	cnt = 0;
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
		free(copy[idx]);
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

typedef struct s_tool
{
	int dir;
	int pivot;
	int push_count;
} t_tool;

typedef struct s_node
{
	int data;
	int score;
	struct s_node *next;
}	t_node;

typedef struct s_cmd_node
{
	struct s_cmd_node *next;
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

int	insert_pivot_list(t_pivot_list *list, int stack, int pivot, int push_count)
{
	t_pivot_node *new_node = malloc(sizeof(t_pivot_node));
	if (!new_node)
	{
		// free split;
		return (1);
	}
	new_node->tool.dir = stack;
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
			printf("cur->data:%d ", cur->data);
			printf("score:%d ", cur->score);
			cur = cur->next;
		}
		printf("\n");
	}
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
	t_node *cur;
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
				printf("sa\n");
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
				printf("rb\n");
				printf("pa\n");
				printf("pa\n");
				command_cnt += 3;
			}
			else
			{
				pa(list1, list2);
				pa(list1, list2);
				printf("pa\n");
				printf("pa\n");
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
				printf("rb\n");
				printf("pa\n");
				printf("rrb\n");
				printf("pa\n");
				command_cnt += 4;
			}
			else
			{
				pa(list1, list2);
				pa(list1, list2);
				printf("pa\n");
				printf("pa\n");
				command_cnt += 2;
			}
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

void	push_stack(t_list *list1, t_list *list2, t_pivot_list **pivot_list)
{
	t_pivot_node	*cur;
	int				pivot;
	int				pivot1;
	int				pivot2;
	int				cnt;
	int				p_count;
	int				alone;

	cur = (*pivot_list)->tail;
	pivot = cur->tool.pivot;
	alone = 0;
	if (cur->tool.push_count <= 2)
	{
		if (cur->tool.push_count == 2)
		{
			if (cur->tool.dir == 0)
				compare_two_sort_list(list1, list2, 0);		
			if (cur->tool.dir == 1)
				compare_two_sort_list(list1, list2, 1);
		}
		if (cur->tool.dir == 1 && cur->tool.push_count == 1)
		{
			printf("pa\n");
			pa(list1, list2);
			++command_cnt;
		}
		delete_pivot_node(pivot_list);
		return ;
	}
	p_count = 0;
	if (list1->cnt == cur->tool.push_count)
		alone = 1;
	if (cur->tool.dir == 0)
	{
		pivot1 = cur->tool.pivot - cur->tool.push_count / 3;
		pivot2 = cur->tool.pivot - cur->tool.push_count / 3 * 2;

		int origin_push_count = cur->tool.push_count;
		cnt = origin_push_count;
		int rotate = 0;
		while (--cnt >= 0)
		{
			if (list_at_score(list1, 0) <= pivot2)
			{
				pb(list1, list2);
				printf("pb\n");
				++p_count;
				++command_cnt;
			}
			else
			{
				ra(list1);
				printf("ra\n");
				++command_cnt;
			}
		}
		delete_pivot_node(pivot_list);

		insert_pivot_list(*pivot_list, 1, pivot2, p_count);
		rotate = origin_push_count - p_count;
		(origin_push_count) -= p_count;
		while (!alone && --rotate >= 0)
		{
			rra(list1);
			printf("rra\n");
			++command_cnt;
		}
		p_count = 0;
		cnt = origin_push_count; 
		while (--cnt >= 0)
		{
			if (list_at_score(list1, 0) <= pivot1)
			{
				pb(list1, list2);
				printf("pb\n");
				++p_count;
				++command_cnt;
			}
			else
			{
				ra(list1);
				printf("ra\n");
				++command_cnt;
			}
		}
		origin_push_count -= p_count; 
		insert_pivot_list(*pivot_list, 1, pivot1, p_count);
		rotate = origin_push_count;
		while (!alone && --rotate >= 0)
		{
			rra(list1);
			printf("rra\n");
			++command_cnt;
		}
		insert_pivot_list(*pivot_list, 0, pivot, origin_push_count);
	}
	else
	{
		int origin_push_count = cur->tool.push_count;
		cnt = origin_push_count;
		int rotate = 0;
		pivot1 = cur->tool.pivot - cur->tool.push_count / 2;
		while (--cnt >= 0)
		{
			if (list_at_score(list2, 0) >= pivot1)
			{
				pa(list1, list2);
				printf("pa\n");
				++p_count;
				++command_cnt;
			}
			else
			{
				rb(list2);
				printf("rb\n");
				++command_cnt;
			}
		}
		delete_pivot_node(pivot_list);

		insert_pivot_list(*pivot_list, 1, pivot - p_count, origin_push_count - p_count);
		insert_pivot_list(*pivot_list, 0, pivot, p_count);
		p_count = origin_push_count - p_count;
		while (!alone && --p_count >= 0)
		{
			rrb(list2);
			printf("rrb\n");
			++command_cnt;
		}
	}
}

void	recur(t_list *list1, t_list *list2, t_pivot_list *pivot_list)
{
	while (pivot_list->cnt > 0)
	{
		push_stack(list1, list2, &pivot_list);
	}
}


int	main(int argc, char *argv[])
{
	int		i;
	int		j; int		number;
	int		element_cnt;
	char	**element;

	t_list		stack_a;
	t_list		stack_b;
	t_list		temp;
	t_pivot_list	pivot_list;

	init_list(&stack_a);
	init_list(&stack_b);
	init_list(&temp);
	init_pivot_list(&pivot_list);
	i = 0;
	printf("argc: %d\n", argc);
	while (++i < argc)
	{
		element_cnt = count_word(argv[i]);
		element = ft_split(argv[i]);
		j = -1;
		while (++j < element_cnt)
		{
			number = ft_atoi(element[j]);
			if (number == 0 && !check_real_zero(element[j]))
			{
				printf("error: invalid argument\n");
				//free_split
				//free_list
				return (0);
			}
			else
			{
				if (insert_list(&temp, number) == 1 || insert_list(&stack_a, number) == 1)
				{
					printf("error: list malloc failed\n");
					//free_split;
					//free_list;
					return (0);
				}
			}
		}
	}
	if (check_duplicate_number(stack_a) == 1)
	{
		printf("error: duplicate number\n");
		//free_split
		//free_list
		return (0);
	}
	quick_sort(&temp, 0, temp.cnt - 1);
	mark_rank(&temp, &stack_a);
	insert_pivot_list(&pivot_list, 0, stack_a.cnt, stack_a.cnt);

	recur(&stack_a, &stack_b, &pivot_list);
	printf("\n\nstack_a\n");
	iterate_list(stack_a);
	printf("\n\nstack_b\n");
	iterate_list(stack_b);
	printf("command_cnt: %d\n", command_cnt);
	return (0);
}
