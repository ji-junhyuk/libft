/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:10:55 by junji             #+#    #+#             */
/*   Updated: 2022/09/18 14:37:05 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus_includes/checker.h"
#include "../bonus_includes/print.h"

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

int	main(int argc, char *argv[])
{
	t_list			stack_a;
	t_list			stack_b;

	init_list(&stack_a, &stack_b);
	if (argc == 1)
		return (0);
	if (check_valid_input(argc, argv, &stack_a) == 1)
		put_error(ERROR_MESSAGE);
	if (check_duplicate_list(stack_a) == 1)
		put_error(ERROR_MESSAGE);
	if (get_stdin(&stack_a, &stack_b) == 1)
		put_error(ERROR_MESSAGE);
	if (is_sorted(&stack_a) && stack_b.cnt == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack(&stack_a, &stack_b);
}
