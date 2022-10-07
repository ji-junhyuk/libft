/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:12:11 by junji             #+#    #+#             */
/*   Updated: 2022/10/07 15:27:41 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parse.h"
#include "../includes/pipe.h"
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

void	init_pipe_tool(t_pipe *pipe_tool, int argc, char *argv[])
{
	pipe_tool->argc = argc;
	pipe_tool->argv = argv;
	pipe_tool->i = 1;
	pipe_tool->fdin = open(argv[1], O_RDONLY);
	if (pipe_tool->fdin == -1)
	{
		perror("open");
		exit(1);
	}
}
