/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:12:11 by junji             #+#    #+#             */
/*   Updated: 2022/10/06 17:29:30 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/parse_bonus.h"
#include "../includes_bonus/pipe_bonus.h"
#include "../includes_bonus/string_utils_bonus.h"
#include <stdlib.h>
#include <fcntl.h>

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
	pipe_tool->heredoc = 0;
	pipe_tool->i = 1;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0) // 추가로 argv[2]가 cmd가 아닐 때
	{
		pipe_tool->heredoc = 1;
		pipe_tool->i = 2;
	}
	pipe_tool->fdin = open(argv[1], O_CREAT | O_RDWR, 00666);
}
