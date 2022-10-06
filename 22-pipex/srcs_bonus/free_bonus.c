/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:12:04 by junji             #+#    #+#             */
/*   Updated: 2022/10/06 22:01:15 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/parse_bonus.h"
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

void	delete_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd_node	*cur;
	t_cmd_node	*temp;

	cur = cmd_list->head;
	while (--cmd_list->cnt >= 0)
	{
		temp = cur;
		cur = cur->next;
		free_arr(temp->cmd);
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
