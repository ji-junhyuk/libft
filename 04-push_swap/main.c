/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:47:02 by junji             #+#    #+#             */
/*   Updated: 2022/08/30 16:56:37 by junji            ###   ########.fr       */
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
}	t_cmd_node;

typedef struct s_list
{
	t_node	*tail;
	int		cnt;
}	t_list;


typedef struct s_cmd_list
{
	t_cmd_node	*tail;
	int 	cnt;
}	t_cmd_list;

void	init_list(t_list *list)
{
	list->tail = NULL;
	list->cnt = 0;
}

void	init_cmd_list(t_cmd_list *list)
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

int	insert_cmd_list(t_cmd_list *list, int stack, int pivot, int push_count)
{
	t_cmd_node *new_node = malloc(sizeof(t_cmd_node));
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
			printf("cur->data:%d\n", cur->data);
			printf("score:%d\n", cur->score);
			cur = cur->next;
		}
	}
}

void	iterate_cmd_list(t_cmd_list list)
{
	t_cmd_node *cur;

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
	cur = list2->tail->next;
	printf("pa_data:%d\n", cur->data);
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
	//left >= 0
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
	{
		printf("list_at_score\n");
		first = first->next;
	}
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

void compare_two(t_list *list)
{
	int score1 = list_at_score(list, 0);
	int score2 = list_at_score(list, 1);
	if (score1 > score2)
	{
		printf("compare: ra\n");
		ra(list);
		++command_cnt;
	}
}

void push_stack_b(t_list *list1, t_list *list2, t_cmd_list *cmd_list, int pivot)
{
	int cnt;
	int order_count = 0;
	cnt = list1->cnt;
	int pivot1 = pivot + cnt / 3;
	int pivot2 = pivot + cnt / 3 * 2;
	if (cnt <= 2)
	{
		printf("list1.cnt: %d\n", list1->cnt);
		compare_two(list1);
		return ;
	}
	int push_count = 0;
	printf("cnt: %d\n", cnt);
	printf("pivot1: %d\n", pivot1);
	while (--cnt >= 0)
	{
		if (list_at_score(list1, 0) <= pivot1)
		{
			pb(list1, list2);
			++command_cnt;
			++push_count;
		}
		else
		{
			ra(list1);
			++command_cnt;
		}
		++order_count;
	}
	insert_cmd_list(cmd_list, 1, pivot1, push_count);
	printf("push_count1:%d\n", push_count);
	cnt = list1->cnt;
	printf("cnt: %d\n", cnt);
	printf("pivot2: %d\n", pivot2);
	push_count = 0;
	while (--cnt >= 0)
	{
		if (list_at_score(list1, 0) <= pivot2)
		{
			pb(list1, list2);
			++push_count;
			++command_cnt;
		}
		else
		{
			ra(list1);
			++command_cnt;
		}
		++order_count;
	}
	printf("push_count2:%d\n", push_count);
	printf("order_count:%d\n", order_count);
	insert_cmd_list(cmd_list, 1, pivot2, push_count);
	push_stack_b(list1, list2, cmd_list, pivot2);
}

void	compare_two_sort_list(t_list *list1, t_list *list2, int flag)
{
	(void) flag;
	int score1 = list_at_score(list2, 0);
	int score2 = list_at_score(list2, 1);

	int score3 = list_at_score(list1, 0);
	int score4 = list_at_score(list1, 1);
	if (flag == 0)
	{
			if (score3 > score4)
			{
				sa(list1);
			}
	}
	else
	{
		if (list2->cnt == 2) //  갯수가 2개일 때
		{
			if (score1 < score2)
			{
				rb(list2);
				pa(list1, list2);
				pa(list1, list2);
				command_cnt += 3;
			}
			else
			{
				pa(list1, list2);
				pa(list1, list2);
				command_cnt += 2;
			}
		}
		else // 더 많을 때
		{
			if (score1 < score2)
			{
				rb(list2);
				pa(list1, list2);
				rrb(list2);
				pa(list1, list2);
				command_cnt += 4;
			}
			else
			{
				pa(list1, list2);
				pa(list1, list2);
				command_cnt += 2;
			}
		}
	}
}

int	delete_node(t_list *list)
{
	t_node *del_pos;
	int		del_data;

	if (list->cnt == 0)
		return (0);
	del_pos = list->tail->next;
	//free(del_pos);
	del_data = del_pos->data;
	list->tail->next = del_pos->next;
	free(del_pos);
	if (list->cnt == 1)
		list->tail = NULL;
	--(list->cnt);
	return (del_data);
}

//void	delete_cmd_list(t_cmd_list *cmd_list)
//{
//	t_cmd_node *temp;
//	t_cmd_node *tail_prev;
//	int			cnt;
//
//	printf("delete_cmd_list\n");
//	printf("pivot: %d\n", cmd_list->tail->tool.pivot);
//	cnt = cmd_list->cnt;
//	if (cnt <= 0)
//		return ;
//	temp = cmd_list->tail;
//	tail_prev = cmd_list->tail;
//	while (--cnt)
//		tail_prev = tail_prev->next;
//	printf("delete_cmd_list, tail_prev->pivot: %d\n", tail_prev->tool.pivot);
//	cmd_list->tail = tail_prev;
//	tail_prev->next = cmd_list->tail->next;
//	free(temp);
//	temp = NULL;
//	--(cmd_list->cnt);
//}
void	delete_cmd_list(t_cmd_list **cmd_list)
{
	t_cmd_node *temp;
	t_cmd_node *tail_prev;
	int			cnt;

	printf("delete_cmd_list\n");
	printf("pivot: %d\n", (*cmd_list)->tail->tool.pivot);
	cnt = (*cmd_list)->cnt;
	if (cnt <= 0)
		return ;
	temp = (*cmd_list)->tail;
	tail_prev = (*cmd_list)->tail;
	while (--cnt)
		tail_prev = tail_prev->next;
	printf("delete_cmd_list, tail_prev->pivot: %d\n", tail_prev->tool.pivot);
	tail_prev->next = (*cmd_list)->tail->next;
	(*cmd_list)->tail = tail_prev;
	free(temp);
	temp = NULL;
	--((*cmd_list)->cnt);
}

void	push_stack_b_r(t_list *list1, t_list *list2, t_cmd_list *cmd_list)
{
	t_tool tool;

	tool = cmd_list->tail->tool;
	int pivot1 = tool.pivot + tool.push_count / 3; //27
	int pivot2 = tool.pivot + tool.push_count / 3 * 2; //26
	printf("push_stack_b_r, pivot1: %d\n", pivot1);
	printf("push_stack_b_r, pivot2: %d\n", pivot2);
	if (tool.push_count <= 2)
	{
		if (tool.push_count == 1)
			pa(list1, list2);
		else
			compare_two_sort_list(list1, list2, 0);
		delete_cmd_list(&cmd_list);
		printf("cmd_list2\n");
		iterate_cmd_list(*cmd_list);
		return ;
	}
	else 
	{
		int push_count = 0;
		int cnt;
		cnt = tool.push_count;
		while (--cnt >= 0)
		{
			if (list_at_score(list1, 0) >= pivot1)
			{
				pa(list1, list2);
				++command_cnt; ++push_count;
				--tool.push_count;
			}
			else
			{
				rb(list2);
				++command_cnt;
			}
		}
		delete_cmd_list(&cmd_list);
		insert_cmd_list(cmd_list, 0, pivot1, push_count);
		int rrb_count = tool.push_count - push_count;
		while (--rrb_count >= 0)
			rrb(list2);
		tool.push_count -= push_count;
		printf("****cmd_list2\n");
		iterate_cmd_list(*cmd_list);
		return ; 
	} 
} 

void	push_stack_a_r(t_list *list1, t_list *list2, t_cmd_list **cmd_list)
{
	t_tool tool;

	tool = (*cmd_list)->tail->tool;
	int pivot1 = tool.pivot - tool.push_count / 3; //27
	int pivot2 = tool.pivot - tool.push_count / 3 * 2; //26
	printf("push_stack_a_r, pivot1: %d\n", pivot1);
	printf("push_stack_a_r, pivot2: %d\n", pivot2);
	if (tool.push_count <= 2)
	{
		if (tool.push_count == 1)
			pa(list1, list2);
		else
			compare_two_sort_list(list1, list2, 0);
		delete_cmd_list(cmd_list);
		return ;
	}
	else 
	{
		int push_count = 0;
		int cnt;
		cnt = tool.push_count;
		int rb_count = 0;
		printf("\n\nbefore itera\n");
		iterate_list(*list1);
		printf("\niter b\n");
		iterate_list(*list2);
		while (--cnt >= 0)
		{
//			printf("\n*list_at_score:%d\n", list_at_score(list1, 0));
			if (list_at_score(list2, 0) >= pivot1)
			{
				pa(list1, list2);
				++command_cnt;
				++push_count;
				--tool.push_count;
			}
			else
			{
				rb(list2);
				++rb_count;
				++command_cnt;
			}
		}
		printf("\n\n itera\n");
		iterate_list(*list1);
		int rrb_count = rb_count; //2
		printf("push_stack_a_r, rrb_count:%d\n", rrb_count);
		while (--rrb_count >= 0)
			rrb(list2);
		(*cmd_list)->tail->tool.pivot = pivot2;
		(*cmd_list)->tail->tool.push_count = tool.push_count - push_count;
		insert_cmd_list(*cmd_list, 0, pivot1, push_count);
		printf("\n****cmd_list2\n");
		iterate_cmd_list(*(*cmd_list));
		return ;

//		cnt = tool.push_count;
//		push_count = 0;
		
		(*cmd_list)->tail->tool.pivot = pivot2;
//		while (--cnt >= 0)
//		{
//			if (list_at_score(list1, 0) >= pivot2)
//			{
//				pa(list1, list2);
//				++command_cnt;
//				++push_count;
//				--tool.push_count;
//			}
//			else
//			{
//				rb(list2);
//				++rb_count;
//				++command_cnt;
//			}
//		}
//		while (--rb_count >= 0)
//			rrb(list2);
//		insert_cmd_list(cmd_list, 0, pivot2, push_count);
	}
}

void	delete_cmd_node(t_list *list1, t_list *list2, t_cmd_list *cmd_list)
{
	t_cmd_node *cur;

	cur = cmd_list->tail;
	printf("=========================\n");
	while (cmd_list->cnt > 0)
	{
		sleep(2);
		printf("cmd_list->cnt: %d\n", cmd_list->cnt);
		printf("iter a\n");
		iterate_list(*list1);
		printf("iter b\n");
		iterate_list(*list2);
		printf("iter command\n");
		iterate_cmd_list(*cmd_list);
		if (cur->tool.dir == 1)
		{
			push_stack_a_r(list1, list2, &cmd_list);
		}
		else
		{
			push_stack_b_r(list1, list2, cmd_list);
		}
		cur = cmd_list->tail;
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
	t_cmd_list	command;
	t_cmd_list*	command_ptr;


	command_ptr = &command;
	init_list(&stack_a);
	init_list(&stack_b);
	init_list(&temp);
	init_cmd_list(&command);
	i = 0;
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
	printf("sort temp? :%d\n", is_sorted(&temp));
	mark_rank(&temp, &stack_a);
	printf("stack_a sort? :%d\n", is_sorted(&stack_a));
	push_stack_b(&stack_a, &stack_b, &command, 0); // 1. create_node;
	printf("************=push_stack_a_r\n");
	printf("iter a\n");
	iterate_list(stack_a);
	printf("iter b\n");
	iterate_list(stack_b);

												   //
	printf("iter command\n");
	iterate_cmd_list(command);

	printf("delete_cmd_node\n");
	delete_cmd_node(&stack_a, &stack_b, &command);

	printf("iter a\n");
	iterate_list(stack_a);
	printf("iter b\n");
	iterate_list(stack_b);
	printf("command_cnt: %d\n", command_cnt);
//	printf("iter command\n");
//	iterate_cmd_list(command);
//	delete_cmd_list(&command_ptr);
	return (0);
}
