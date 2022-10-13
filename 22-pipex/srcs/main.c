/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:21:46 by junji             #+#    #+#             */
/*   Updated: 2022/10/13 17:00:04 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "error.h"
#include "string_utils.h"
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

void	communicate_pipe(t_pipe *pipe_tool, t_path_list *path_list)
{
	pipe_tool->pid = fork();
	if (pipe_tool->pid == -1)
		fork_error();
	if (pipe_tool->pid == 0)
	{
		if (pipe_tool->i == 2)
		{
			pipe_tool->prev_pipe_in = open("infile", O_RDONLY, 00666);
			if (pipe_tool->prev_pipe_in == -1)
				open_error();
		}
		if (dup2(pipe_tool->prev_pipe_in, 0) == -1)
			dup2_error();
		if (close(pipe_tool->prev_pipe_in) == -1)
			close_error();
		if (dup2(pipe_tool->curr_pipe_out, 1) == -1)
			dup2_error();
		if (close(pipe_tool->curr_pipe_out) == -1)
			close_error();
		if (pipe_tool->i != 3)
			close(pipe_tool->curr_pipe_in);
		pipe_tool->cmd = get_cmd(path_list, pipe_tool);
		if (execve(pipe_tool->cmd, pipe_tool->exec_argv, 0) == -1)
			execve_error();
	}
}

void	pipex(t_pipe *p_tool, t_path_list *path_list)
{
	while (++p_tool->i < (p_tool->argc - 1))
	{
		if (p_tool->i == (p_tool->argc - 2))
			p_tool->curr_pipe_out = open(p_tool->argv[p_tool->argc - 1],
					O_CREAT | O_TRUNC | O_WRONLY, 00666);
		else
		{
			if (pipe(p_tool->fdpipe) == -1)
				return (pipe_error());
			p_tool->curr_pipe_in = p_tool->fdpipe[0];
			p_tool->curr_pipe_out = p_tool->fdpipe[1];
		}
		communicate_pipe(p_tool, path_list);
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
}

int	main(int argc, char *argv[], char *envp[])
{
	t_path_list	path_list;
	t_pipe		pipe_tool;

	if (argc != 5)
		invalid_argument();
	parse_path(envp, &path_list);
	init_pipe_tool(&pipe_tool, argc, argv);
	pipex(&pipe_tool, &path_list);
	delete_path_list(&path_list);
	return (0);
}
