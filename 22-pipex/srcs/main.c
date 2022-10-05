/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:21:46 by junji             #+#    #+#             */
/*   Updated: 2022/10/05 15:40:12 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"
#include "../includes/pipe.h"

void	communicate_pipe(t_pipe *pipe_tool,
		t_path_list *path_list, t_cmd_list *cmd_list)
{
	pipe_tool->c_node = cmd_list->head;
	pipe_tool->idx = pipe_tool->i - 2;
	while (--(pipe_tool->idx) >= 0)
		pipe_tool->c_node = pipe_tool->c_node->next;
	pipe_tool->cmd = get_cmd(path_list, cmd_list, pipe_tool->i - 2);
	execve(pipe_tool->cmd, pipe_tool->c_node->cmd, 0);
}

void	pipex(t_pipe *pipe_tool, t_path_list *path_list, t_cmd_list *cmd_list)
{
	while (++pipe_tool->i < (pipe_tool->argc - 1))
	{
		dup2(pipe_tool->fdin, 0);
		close(pipe_tool->fdin);
		if (pipe_tool->i == (pipe_tool->argc - 2))
			pipe_tool->fdout = open(pipe_tool->argv[pipe_tool->argc - 1],
					O_CREAT | O_TRUNC | O_WRONLY, 00666);
		else
		{
			pipe(pipe_tool->fdpipe);
			pipe_tool->fdin = pipe_tool->fdpipe[0];
			pipe_tool->fdout = pipe_tool->fdpipe[1];
		}
		dup2(pipe_tool->fdout, 1);
		close(pipe_tool->fdout);
		pipe_tool->pid = fork();
		if (pipe_tool->pid == -1)
			exit(1);
		if (pipe_tool->pid == 0)
			communicate_pipe(pipe_tool, path_list, cmd_list);
	}
	waitpid(pipe_tool->pid, NULL, 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_path_list	path_list;
	t_cmd_list	cmd_list;
	t_pipe		pipe_tool;

	if (argc != 5)
		exit(1);
	parse_path(envp, &path_list);
	parse_cmd(argc, argv, &path_list, &cmd_list);
	init_pipe_tool(&pipe_tool, argc, argv);
	pipex(&pipe_tool, &path_list, &cmd_list);
//	delete_list(&path_list, &cmd_list);
	delete_path_list(&path_list);
	delete_cmd_list(&cmd_list);
	return (0);
}
