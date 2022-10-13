/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:12:04 by junji             #+#    #+#             */
/*   Updated: 2022/10/13 16:59:43 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>

void	delete_path_list(t_path_list *path_list)
{
	t_path_node	*cur;
	t_path_node	*temp;

	cur = path_list->head;
	while (--path_list->cnt >= 0)
	{
		temp = cur;
		cur = cur->next;
		free(temp->path);
		free(temp);
		temp = 0;
	}
}

void	free_arr(char **arr)
{
	int	idx;

	idx = -1;
	while (arr[++idx])
	{
		free(arr[idx]);
		arr[idx] = 0;
	}
	free(arr);
	arr = 0;
}
