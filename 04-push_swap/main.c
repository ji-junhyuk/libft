/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:47:02 by junji             #+#    #+#             */
/*   Updated: 2022/08/19 17:04:38 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

typedef struct s_node
{
	int data;
	struct s_node *next;
}	t_node;

typedef struct s_list
{
	t_node	*tail;
	int		cnt;
}	t_list;

void	init_list(t_list *list)
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

int	insert_front_list(t_list *list, int number)
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
			printf("%d\n", cur->data);
			cur = cur->next;
		}
	}
}

int	check_duplicate_number(t_list list)
{
	t_node *cur;

	if (list.cnt <= 1)
		return (0);
	cur = list.tail->next;
	while (list.cnt)
	{
		while (cur != list.tail)
		{
			if (list.tail->data == cur->data)
				return (1);
			cur = cur->next;
		}
		list.tail = list.tail->next;
		list.cnt--;
	}
	return (0);
}

int	delete_node(t_list *list)
{
	t_node *del_pos;
	int		del_data;

	if (list->cnt == 0)
		return (0);
	del_pos = list->tail->next;
	del_data = del_pos->data;
	list->tail->next = del_pos->next;
	free(del_pos);
	if (list->cnt == 1)
		list->tail = NULL;
	--(list->cnt);
	return (del_data);
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
	int	number;

	if (list1->cnt <= 0)
		return (0);
	number = delete_node(list1);
	insert_front_list(list2, number);
	return (0);
}

int pa(t_list *list1, t_list *list2)
{
	int number;

	if (list2->cnt <= 0)
		return (0);
	number = delete_node(list2);
	insert_front_list(list1, number);
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

int	main(int argc, char *argv[])
{
	int		i;
	int		j;
	int		number;
	int		element_cnt;
	char	**element;
	t_list	stack_a;
	t_list	stack_b;

	init_list(&stack_a);
	init_list(&stack_b);
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
				if (insert_list(&stack_a, number) == 1)
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
	printf("cnt:%d\n", stack_a.cnt);
	iterate_list(stack_a);
	printf("rra\n");
	rra(&stack_a);
	iterate_list(stack_a);
	printf("rra\n");
	rra(&stack_a);
	iterate_list(stack_a);
	return (0);
}
