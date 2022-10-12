/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:12:40 by junji             #+#    #+#             */
/*   Updated: 2022/10/12 20:29:19 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <unistd.h>
# include <fcntl.h>
# include "parse.h"

typedef struct s_pipe
{
	int			argc;
	char		**argv;
	int			i;
	int			curr_pipe_in;
	int			curr_pipe_out;
	int			prev_pipe_in;
	int			fdpipe[2];
	char		*cmd;
	char		**exec_argv;
	pid_t		pid;
}	t_pipe;

char	*get_cmd(t_path_list *path_list, t_pipe *pipe_tool);
void	init_pipe_tool(t_pipe *pipe_tool, int argc, char *argv[]);
void	parse_path(char *envp[], t_path_list *path_list);
void	parse_cmd(int argc, char *argv[], t_path_list *path_list);
void	delete_path_list(t_path_list *path_list);

#endif
