/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:55:20 by junji             #+#    #+#             */
/*   Updated: 2022/10/13 17:01:51 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"
#include "error_bonus.h"
#include "string_utils_bonus.h"
#include "string_utils2_bonus.h"
#include <stdlib.h>

char	*get_cmd(t_path_list *path_list, t_pipe *pipe_tool)
{
	t_path_node	*p_node;
	char		*all_path;
	int			p_count;
	int			access_code;

	pipe_tool->exec_argv = ft_split(pipe_tool->argv[pipe_tool->i], ' ');
	p_count = path_list->cnt;
	p_node = path_list->head;
	while (--p_count >= 0)
	{
		all_path = ft_strjoin(p_node->path, pipe_tool->exec_argv[0]);
		access_code = access(all_path, F_OK | X_OK);
		if (access_code == 0)
			return (all_path);
		free(all_path);
		p_node = p_node->next;
	}
	return (0);
}

void	open_file(t_pipe *pipe_tool)
{
	if (pipe_tool->heredoc == 1 && pipe_tool->i == 3)
	{
		pipe_tool->prev_pipe_in = open(pipe_tool->argv[1], O_RDONLY);
		if (pipe_tool->prev_pipe_in == -1)
			open_error();
	}
	if (pipe_tool->i == 2)
	{
		pipe_tool->prev_pipe_in = open(pipe_tool->argv[1], O_RDONLY);
		if (pipe_tool->prev_pipe_in == -1)
			open_error();
	}
}

void	execute_command(t_pipe *pipe_tool, t_path_list *path_list)
{
	if (pipe_tool->pid == 0)
	{
		open_file(pipe_tool);
		if (dup2(pipe_tool->prev_pipe_in, 0) == -1)
			dup2_error();
		if (close(pipe_tool->prev_pipe_in) == -1)
			close_error();
		if (dup2(pipe_tool->curr_pipe_out, 1) == -1)
			dup2_error();
		if (close(pipe_tool->curr_pipe_out) == -1)
			close_error();
		if (pipe_tool->i != pipe_tool->argc - 2)
		{
			if (close(pipe_tool->curr_pipe_in) == -1)
				close_error();
		}
		pipe_tool->cmd = get_cmd(path_list, pipe_tool);
		if (execve(pipe_tool->cmd, pipe_tool->exec_argv, 0) == -1)
			execve_error();
	}
}

void	set_pipe(t_pipe *pipe_tool)
{
	if (pipe_tool->i == (pipe_tool->argc - 2))
		pipe_tool->curr_pipe_out = open(pipe_tool->argv[pipe_tool->argc - 1],
				pipe_tool->flag, 00666);
	else
	{
		if (pipe(pipe_tool->fdpipe) == -1)
			return (pipe_error());
		pipe_tool->curr_pipe_in = pipe_tool->fdpipe[0];
		pipe_tool->curr_pipe_out = pipe_tool->fdpipe[1];
	}
}

void	pipex(t_pipe *p_tool, t_path_list *path_list)
{
	if (p_tool->heredoc)
		get_line(p_tool);
	while (++p_tool->i < (p_tool->argc - 1))
	{
		set_pipe(p_tool);
		p_tool->pid = fork();
		if (p_tool->pid == -1)
			fork_error();
		execute_command(p_tool, path_list);
		if (p_tool->prev_pipe_in >= 0)
		{
			if (close(p_tool->prev_pipe_in) == -1)
				close_error();
		}
		p_tool->prev_pipe_in = p_tool->curr_pipe_in;
		if (close(p_tool->curr_pipe_out) == -1)
			close_error();
	}
	if (waitpid(p_tool->pid, NULL, 0) == -1)
		waitpid_error();
	if (p_tool->heredoc)
		unlink(p_tool->argv[1]);
}
