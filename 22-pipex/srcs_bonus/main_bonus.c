/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:27:04 by junji             #+#    #+#             */
/*   Updated: 2022/10/06 22:32:21 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipe_bonus.h"
#include "../includes_bonus/error_bonus.h"
#include "../includes_bonus/string_utils_bonus.h"
#include "../includes_bonus/string_utils2_bonus.h"
#include <fcntl.h>
#include <stdlib.h>

void	communicate_pipe(t_pipe *pipe_tool,
		t_path_list *path_list, t_cmd_list *cmd_list)
{
	int	zero;

	zero = 2;
	if (pipe_tool->heredoc == 1)
		++zero;
	pipe_tool->pid = fork();
	if (pipe_tool->pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pipe_tool->pid == 0)
	{
		pipe_tool->c_node = cmd_list->head;
		pipe_tool->idx = pipe_tool->i - zero;
		while (--(pipe_tool->idx) >= 0)
			pipe_tool->c_node = pipe_tool->c_node->next;
		pipe_tool->cmd = get_cmd(path_list, cmd_list, pipe_tool->i - zero);
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

void	get_line(t_pipe *pipe_tool)
{	
	char	*line;
	int		pipe_cnt;

	while (1)
	{
		pipe_cnt = pipe_tool->argc - 5;
		while (--pipe_cnt >= 0)
			write(1, "pipe ", 5);
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (ft_strncmp(line, pipe_tool->argv[2],
				ft_strlen(pipe_tool->argv[2])) == 0
			&& (ft_strlen(pipe_tool->argv[2]) == ft_strlen(line) - 1))
			break ;
		write(pipe_tool->fdin, line, ft_strlen(line));
	}
	if (close(pipe_tool->fdin) == -1)
		return (close_error());
	if (open(pipe_tool->argv[1], O_RDWR, 00666) == -1)
	{
		perror("get_line open");
		exit(1);
	}
}

void	heredoc(t_pipe *pipe_tool, t_path_list *path_list, t_cmd_list *cmd_list)
{		
	while (++pipe_tool->i < (pipe_tool->argc - 1))
	{
		if (dup2(pipe_tool->fdin, 0) == -1)
			dup2_error();
		if (close(pipe_tool->fdin) == -1)
			return (close_error());
		if (pipe_tool->i == (pipe_tool->argc - 2))
			pipe_tool->fdout = open(pipe_tool->argv[pipe_tool->argc - 1],
					O_CREAT | O_WRONLY | O_APPEND, 00666);
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
	unlink(pipe_tool->argv[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_path_list	path_list;
	t_cmd_list	cmd_list;
	t_pipe		pipe_tool;

	if (argc < 5)
	{
		write(2, "Invalid input\n", 14);
		exit(1);
	}
	parse_path(envp, &path_list);
	init_pipe_tool(&pipe_tool, &path_list, argc, argv);
	parse_cmd(&pipe_tool, &path_list, &cmd_list);
	if (pipe_tool.heredoc == 1)
	{
		get_line(&pipe_tool);
		heredoc(&pipe_tool, &path_list, &cmd_list);
	}
	else
		pipex(&pipe_tool, &path_list, &cmd_list);
	delete_path_list(&path_list);
	delete_cmd_list(&cmd_list);
	return (0);
}
