/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:12:20 by junji             #+#    #+#             */
/*   Updated: 2022/10/06 16:32:30 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/parse_bonus.h"
#include "../includes_bonus/error_bonus.h"
#include "../includes_bonus/string_utils_bonus.h"
#include "../includes_bonus/pipe_bonus.h"
#include <unistd.h>

void	insert_cmd_list(t_cmd_list *list, char *cmd)
{
	t_cmd_node	*node;

	node = malloc(sizeof(t_path_node));
	if (!node)
	{
		perror("insert_cmd malloc");
		exit(1);
	}
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
		if (access(all_path, F_OK | X_OK) == 0)
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
	int			access_code;

	p_count = path_list->cnt;
	p_node = path_list->head;
	c_node = cmd_list->head;
	while (--cnt >= 0)
		c_node = c_node->next;
	while (--p_count >= 0)
	{
		all_path = ft_strjoin(p_node->path, c_node->cmd[0]);
		access_code = access(all_path, F_OK | X_OK);
		if (access_code == 0)
			return (all_path);
		free(all_path);
		p_node = p_node->next;
	}
	return (0);
}

void	parse_cmd(t_pipe *pipe_tool,
		t_path_list *path_list, t_cmd_list *cmd_list)
{
	int	i;
	int zero;

	i = 1;
	zero = 2;
	if (pipe_tool->heredoc == 1) // 추가로 argv[2]가 cmd가 아닐 때
	{
		++zero;
		i++;
	}
	init_cmd_list(cmd_list);
	while (++i < (pipe_tool->argc - 1))
		insert_cmd_list(cmd_list, pipe_tool->argv[i]);
	i = 1;
	if (pipe_tool->heredoc == 1) // 추가로 argv[2]가 cmd가 아닐 때
		i++;
	while (++i < (pipe_tool->argc - 1))
	{
		if (check_valid_cmd(path_list, cmd_list, i - zero) == 1)
		{
			write(2, "Invalid Command\n", 16);
			exit(1);
		}
	}
}
