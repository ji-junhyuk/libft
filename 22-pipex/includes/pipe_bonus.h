/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:12:40 by junji             #+#    #+#             */
/*   Updated: 2022/10/12 19:58:32 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_BONUS_H
# define PIPE_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include "parse_bonus.h"

typedef struct s_pipe
{
	int			argc;
	char		**argv;
	int			heredoc;
	int			i;
	int			curr_pipe_in;
	int			curr_pipe_out;
	int			prev_pipe_in;
	int			fdpipe[2];
	int			flag;
	char		*cmd;
	char		**exec_argv;
	pid_t		pid;
}	t_pipe;

void	get_line(t_pipe *pipe_tool);
char	*get_cmd(t_path_list *path_list, t_pipe *pipe_tool);
void	init_pipe_tool(t_pipe *pipe_tool, int argc, char *argv[]);
void	parse_path(char *envp[], t_path_list *path_list);
void	delete_path_list(t_path_list *path_list);
void	pipex(t_pipe *p_tool, t_path_list *path_list);

#endif
