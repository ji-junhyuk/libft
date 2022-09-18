/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:04:50 by junji             #+#    #+#             */
/*   Updated: 2022/09/18 14:40:02 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

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

void	init_list(t_list *list1, t_list *list2);
int		check_valid_input(int argc, char *argv[], t_list *stack_a);
int		check_duplicate_list(t_list list);
int		get_stdin(t_list *list1, t_list *list2);
int		check_valid_command(t_list *list1, t_list *list2, char *cmd);
void	free_stack(t_list *list1, t_list *list2);
#endif
