/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:53:48 by junji             #+#    #+#             */
/*   Updated: 2022/10/13 17:01:17 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"
#include "error_bonus.h"
#include "string_utils_bonus.h"
#include "string_utils2_bonus.h"

void	get_line(t_pipe *p_tool)
{	
	char	*line;
	int		pipe_cnt;
	int		prev_pipe_in;

	prev_pipe_in = open(p_tool->argv[1], O_CREAT | O_RDWR, 00666);
	if (prev_pipe_in == -1)
		open_error();
	while (1)
	{
		pipe_cnt = p_tool->argc - 5;
		while (--pipe_cnt >= 0)
			write(1, "pipe ", 5);
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if ((ft_strncmp(line, p_tool->argv[2], ft_strlen(p_tool->argv[2])) == 0)
			&& (ft_strlen(line) == ft_strlen(p_tool->argv[2]) + 1))
		{
			free(line);
			break ;
		}
		write(prev_pipe_in, line, ft_strlen(line));
		free(line);
	}
	if (close(prev_pipe_in) == -1)
		close_error();
}
