/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:12:11 by junji             #+#    #+#             */
/*   Updated: 2022/10/07 15:37:15 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/parse_bonus.h"
#include "../includes_bonus/pipe_bonus.h"
#include "../includes_bonus/string_utils_bonus.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void	init_path_list(t_path_list *list)
{
	list->cnt = 0;
	list->tail = NULL;
	list->head = NULL;
}

void	init_cmd_list(t_cmd_list *list)
{
	list->cnt = 0;
	list->tail = NULL;
	list->head = NULL;
}

void	init_pipe_tool(t_pipe *pipe_tool,
		t_path_list *path_list, int argc, char *argv[])
{
	pipe_tool->argc = argc;
	pipe_tool->argv = argv;
	pipe_tool->heredoc = 0;
	pipe_tool->i = 1;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0
		&& check_argv2_command(path_list, argv[2]) == 0)
	{
		pipe_tool->heredoc = 1;
		pipe_tool->i = 2;
		pipe_tool->fdin = open(argv[1], O_CREAT | O_RDWR, 00666);
	}
	else
		pipe_tool->fdin = open(argv[1], O_RDONLY);
	if (pipe_tool->fdin == -1)
	{
		perror("open");
		exit(1);
	}
}
