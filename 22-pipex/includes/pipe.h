/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:12:40 by junji             #+#    #+#             */
/*   Updated: 2022/10/05 17:58:09 by junji            ###   ########.fr       */
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
	int			fdin;
	int			fdout;
	int			fdpipe[2];
	int			idx;
	pid_t		pid;
	char		*cmd;
	t_cmd_node	*c_node;
}	t_pipe;

char	*get_cmd(t_path_list *path_list, t_cmd_list *cmd_list, int cnt);
void	init_pipe_tool(t_pipe *pipe_tool, int argc, char *argv[]);
void	parse_path(char *envp[], t_path_list *path_list);
void	parse_cmd(int argc, char *argv[],
			t_path_list *path_list, t_cmd_list *cmd_list);
void	delete_path_list(t_path_list *path_list);
void	delete_cmd_list(t_cmd_list *cmd_list);

#endif
