#include "../bonus_includes/checker.h"
#include "../bonus_includes/get_next_line.h"
# define ERROR_MESSAGE "Error\n"
#include <stdio.h>

typedef struct s_node
{
	int				data;
	int				score;
	struct s_node	*next;
}	t_node;

typedef struct s_info_input
{
	int		i;
	int		j;
	int		element_cnt;
	int		number;
	char	**element;
}	t_info_input;

typedef struct s_list
{
	t_node	*tail;
	int		cnt;
}	t_list;

void	ft_putstr(char *str)
{
	ssize_t	len;

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

void	skip_space(char **str)
{
	while (*(*str) && *(*str) == ' ')
		++(*str);
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
		exit(1);
	idx = -1;
	while (++idx < words)
	{
		skip_space(&str);
		word_len = find_word_len(str);
		*(copy + idx) = malloc(sizeof(char) * (word_len + 1));
		if (*(copy + idx) == 0)
			exit(1);
		jdx = -1;
		while (*str && *str != ' ')
			(*(copy + idx))[++jdx] = *str++;
		(*(copy + idx))[++jdx] = 0;
	}
	*(copy + idx) = 0;
	return (copy);
}

void	init_list(t_list *list1, t_list *list2,
		t_list *list3)
{
	ft_memset(list1, 0, sizeof(*list1));
	ft_memset(list2, 0, sizeof(*list2));
	ft_memset(list3, 0, sizeof(*list3));
}

void	free_arr(char **copy, int idx)
{
	int	index;

	index = -1;
	while (++index < idx)
		free(copy[index]);
	free(copy);
}

int	insert_list(t_list *list, int number)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (1);
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
int	check_valid_input(int argc, char *argv[], t_list *temp, t_list *stack_a)
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
				if (insert_list(temp, input.number) == 1
					|| insert_list(stack_a, input.number) == 1)
					return (1);
			}
		}
		free_arr(input.element, input.element_cnt);
	}
	return (0);
}

int	check_duplicate_list(t_list list)
{
	t_node	*cur;
	t_node	*tail;

	tail = list.tail;
	if (list.cnt <= 1)
		return (0);
	while (--list.cnt)
	{
		cur = list.tail->next;
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

int	sa(t_list *list)
{
	t_node	*tail_prev;
	t_node	*temp;
	int		cnt;

	cnt = 3;
	if (list->cnt <= 1)
		return (0);
	temp = list->tail->next;
	tail_prev = list->tail;
	while (--cnt >= 0)
		tail_prev = tail_prev->next;
	if (list->cnt == 2)
	{
		list->tail = list->tail->next;
		return (0);
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

int	sb(t_list *list)
{
	t_node	*tail_prev;
	t_node	*temp;
	int		cnt;

	cnt = 3;
	if (list->cnt <= 1)
		return (0);
	temp = list->tail->next;
	tail_prev = list->tail;
	while (--cnt >= 0)
		tail_prev = tail_prev->next;
	if (list->cnt == 2)
	{
		list->tail = list->tail->next;
		return (0);
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

int	pb(t_list *list1, t_list *list2)
{
	t_node	*cur;

	if (list1->cnt <= 0)
		return (0);
	if (list1->cnt == 1)
	{
		cur = list1->tail;
		list1->tail = NULL;
		--(list1->cnt);
		insert_front_list(list2, cur);
		return (0);
	}
	cur = list1->tail->next;
	list1->tail->next = list1->tail->next->next;
	--(list1->cnt);
	insert_front_list(list2, cur);
	return (0);
}

int	pa(t_list *list1, t_list *list2)
{
	t_node	*cur;

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

int	ss(t_list *list1, t_list *list2)
{
	sa(list1);
	sb(list2);
	return (0);
}

int	ra(t_list *list)
{
	if (list->cnt <= 1)
		return (0);
	list->tail = list->tail->next;
	return (0);
}

int	rb(t_list *list)
{
	if (list->cnt <= 1)
		return (0);
	list->tail = list->tail->next;
	return (0);
}

int	rr(t_list *list1, t_list *list2)
{
	ra(list1);
	rb(list2);
	return (0);
}

int	rra(t_list *list)
{
	int	cnt;

	cnt = list->cnt;
	if (list->cnt <= 1)
		return (0);
	while (--cnt)
		list->tail = list->tail->next;
	return (0);
}

int	rrb(t_list *list)
{
	int	cnt;

	cnt = list->cnt;
	if (list->cnt <= 1)
		return (0);
	while (--cnt)
		list->tail = list->tail->next;
	return (0);
}

int	rrr(t_list *list1, t_list *list2)
{
	rra(list1);
	rrb(list2);
	return (0);
}

int	is_sorted(t_list *list)
{
	int		cnt;
	t_node	*cur;

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

int main(int argc, char *argv[])
{
	t_list			stack_a;
	t_list			stack_b;
	t_list			sorted_stack;

	init_list(&stack_a, &stack_b, &sorted_stack);
	if (check_valid_input(argc, argv, &sorted_stack, &stack_a) == 1)
		put_error(ERROR_MESSAGE);
	if (check_duplicate_list(stack_a) == 1)
		put_error(ERROR_MESSAGE);
	char *cmd;
	while (1)
	{
		cmd = get_next_line(0);
		if (!cmd)
			break ;
		if (ft_strncmp(cmd, "sa\n", 3) == 0)
			sa(&stack_a);
		else if (ft_strncmp(cmd, "sb\n", 3) == 0)
			sb(&stack_b);
		else if (ft_strncmp(cmd, "ss\n", 3) == 0)
			ss(&stack_a, &stack_b);
		else if (ft_strncmp(cmd, "pa\n", 3) == 0)
			pa(&stack_a, &stack_b);
		else if (ft_strncmp(cmd, "pb\n", 3) == 0)
			pb(&stack_a, &stack_b);
		else if (ft_strncmp(cmd, "ra\n", 3) == 0)
			ra(&stack_a);
		else if (ft_strncmp(cmd, "rb\n", 3) == 0)
			rb(&stack_b);
		else if (ft_strncmp(cmd, "rra\n", 4) == 0)
			rra(&stack_a);
		else if (ft_strncmp(cmd, "rrb\n", 4) == 0)
			rrb(&stack_b);
		else if (ft_strncmp(cmd, "rrr\n", 4) == 0)
			rrr(&stack_a, &stack_b);
		else if (ft_strncmp(cmd, "rr\n", 3) == 0)
			rr(&stack_a, &stack_b);
		else
			put_error(ERROR_MESSAGE);
	}
	printf("stack_b_cnt;%d\n", stack_b.cnt);
	if (is_sorted(&stack_a) && stack_b.cnt == 0)
		write(1, "OK\n", 3);
	else
		write(2, "Error\n", 6);
	iterate_list(stack_b);
}
