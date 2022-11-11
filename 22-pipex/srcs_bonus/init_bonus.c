/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:12:11 by junji             #+#    #+#             */
/*   Updated: 2022/11/11 22:22:34 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_bonus.h"
#include "pipe_bonus.h"
#include "string_utils_bonus.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void	init_path_list(t_path_list *list)
{
	list->cnt = 0;
	list->tail = NULL;
	list->head = NULL;
}

void	init_pipe_tool(t_pipe *pipe_tool, int argc, char *argv[])
{
	pipe_tool->argc = argc;
	pipe_tool->argv = argv;
	pipe_tool->i = 1;
	pipe_tool->heredoc = 0;
	pipe_tool->prev_pipe_in = -1;
	pipe_tool->flag = O_CREAT | O_TRUNC | O_WRONLY;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipe_tool->flag = O_CREAT | O_WRONLY | O_APPEND;
		pipe_tool->heredoc = 1;
		++(pipe_tool->i);
	}
}
