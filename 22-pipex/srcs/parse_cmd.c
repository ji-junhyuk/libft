/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:12:20 by junji             #+#    #+#             */
/*   Updated: 2022/10/05 13:49:40 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"
#include "../includes/string_utils.h"
#include <stdlib.h>
#include <unistd.h>

void	insert_cmd_list(t_cmd_list *list, char *cmd)
{
	t_cmd_node	*node;

	node = malloc(sizeof(t_path_node));
	if (!node)
		return ;
	node->cmd = ft_split(cmd, ' ');
	++list->cnt;
	if (list->tail == NULL)
	{
		list->tail = node;
		list->head = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
}

int	check_valid_cmd(t_path_list *path_list, t_cmd_list *cmd_list, int cnt)
{
	t_path_node	*p_node;
	t_cmd_node	*c_node;
	char		*all_path;
	int			p_count;

	p_count = path_list->cnt;
	p_node = path_list->head;
	c_node = cmd_list->head;
	while (--cnt >= 0)
		c_node = c_node->next;
	while (--p_count >= 0)
	{
		all_path = ft_strjoin(p_node->path, c_node->cmd[0]);
		if (access(all_path, F_OK) == 0)
		{
			free(all_path);
			return (0);
		}
		free(all_path);
		p_node = p_node->next;
	}
	return (1);
}

char	*get_cmd(t_path_list *path_list, t_cmd_list *cmd_list, int cnt)
{
	t_path_node	*p_node;
	t_cmd_node	*c_node;
	char		*all_path;
	int			p_count;

	p_count = path_list->cnt;
	p_node = path_list->head;
	c_node = cmd_list->head;
	while (--cnt >= 0)
		c_node = c_node->next;
	while (--p_count >= 0)
	{
		all_path = ft_strjoin(p_node->path, c_node->cmd[0]);
		if (access(all_path, F_OK) == 0)
			return (all_path);
		free(all_path);
		p_node = p_node->next;
	}
	return (0);
}

void	parse_cmd(int argc, char *argv[],
	t_path_list *path_list, t_cmd_list *cmd_list)
{
	int	i;

	i = 1;
	init_cmd_list(cmd_list);
	while (++i < argc - 1)
		insert_cmd_list(cmd_list, argv[i]);
	i = 1;
	while (++i < argc - 1)
	{
		if (check_valid_cmd(path_list, cmd_list, i - 2) == 1)
			exit(1);
	}
}
