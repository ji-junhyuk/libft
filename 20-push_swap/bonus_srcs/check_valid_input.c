/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 07:22:00 by junji             #+#    #+#             */
/*   Updated: 2022/09/18 09:23:03 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/checker.h"
#include "../bonus_includes/parse.h"

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
	if (*(str - 1) == '0')
		return (1);
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

int	check_valid_input(int argc, char *argv[], t_list *stack_a)
{
	t_info_input	input;

	ft_memset(&input, 0, sizeof(input));
	while (++input.i < argc)
	{
		input.element_cnt = count_word(argv[input.i]);
		if (input.element_cnt == 0)
			return (1);
		input.element = ft_split(argv[input.i]);
		input.j = -1;
		while (++input.j < input.element_cnt)
		{
			input.number = ft_atoi(input.element[input.j]);
			if (input.number == 0 && !check_real_zero(input.element[input.j]))
				return (free_split(input.element, input.element_cnt));
			else
			{
				if (insert_list(stack_a, input.number) == 1)
					return (1);
			}
		}
		free_arr(input.element, input.element_cnt);
	}
	return (0);
}
