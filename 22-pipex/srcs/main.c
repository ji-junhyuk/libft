/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:21:46 by junji             #+#    #+#             */
/*   Updated: 2022/10/05 18:04:42 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipe.h"
#include "../includes/error.h"
#include <stdlib.h>

void	communicate_pipe(t_pipe *pipe_tool,
		t_path_list *path_list, t_cmd_list *cmd_list)
{
	pipe_tool->pid = fork();
	if (pipe_tool->pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pipe_tool->pid == 0)
	{
		pipe_tool->c_node = cmd_list->head;
		pipe_tool->idx = pipe_tool->i - 2;
		while (--(pipe_tool->idx) >= 0)
			pipe_tool->c_node = pipe_tool->c_node->next;
		pipe_tool->cmd = get_cmd(path_list, cmd_list, pipe_tool->i - 2);
		if (execve(pipe_tool->cmd, pipe_tool->c_node->cmd, 0) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
}

void	pipex(t_pipe *pipe_tool, t_path_list *path_list, t_cmd_list *cmd_list)
{
	while (++pipe_tool->i < (pipe_tool->argc - 1))
	{
		if (dup2(pipe_tool->fdin, 0) == -1)
			dup2_error();
		if (close(pipe_tool->fdin) == -1)
			return (close_error());
		if (pipe_tool->i == (pipe_tool->argc - 2))
			pipe_tool->fdout = open(pipe_tool->argv[pipe_tool->argc - 1],
					O_CREAT | O_TRUNC | O_WRONLY, 00666);
		else
		{
			if (pipe(pipe_tool->fdpipe) == -1)
				return (pipe_error());
			pipe_tool->fdin = pipe_tool->fdpipe[0];
			pipe_tool->fdout = pipe_tool->fdpipe[1];
		}
		if (dup2(pipe_tool->fdout, 1) == -1)
			return (dup2_error());
		if (close(pipe_tool->fdout) == -1)
			return (close_error());
		communicate_pipe(pipe_tool, path_list, cmd_list);
	}
	if (waitpid(pipe_tool->pid, NULL, 0) == -1)
		waitpid_error();
}

int	main(int argc, char *argv[], char *envp[])
{
	t_path_list	path_list;
	t_cmd_list	cmd_list;
	t_pipe		pipe_tool;

	if (argc != 5)
	{
		write(2, "Invalid input\n", 14);
		exit(1);
	}
	parse_path(envp, &path_list);
	parse_cmd(argc, argv, &path_list, &cmd_list);
	init_pipe_tool(&pipe_tool, argc, argv);
	pipex(&pipe_tool, &path_list, &cmd_list);
	delete_path_list(&path_list);
	delete_cmd_list(&cmd_list);
	return (0);
}
