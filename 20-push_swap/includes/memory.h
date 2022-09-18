/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:07:57 by junji             #+#    #+#             */
/*   Updated: 2022/09/18 09:11:05 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "push_swap.h"
# include <stdlib.h>

int		insert_list(t_list *list, int number);
int		insert_pivot_list(t_pivot_list *list,
			int dir, int pivot, int push_count);
int		insert_pivot_list_a_to_b_6(t_pivot_list **pivot_list,
			t_pivot_origin *old_pivot, t_pivot_new *new_pivot);
int		insert_pivot_list_b_to_a_6(t_pivot_list **pivot_list,
			t_pivot_origin *old_pivot, t_pivot_new *new_pivot);

void	delete_pivot_node(t_pivot_list **pivot_list);
void	free_stack(t_list *list1, t_list *list2);
void	free_arr(char **copy, int idx);
int		free_split(char **copy, int idx);

void	*ft_memset(void *b, int c, size_t len);

int		count_word(char *str);
char	**ft_split(char *str);

#endif
