/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:21:46 by junji             #+#    #+#             */
/*   Updated: 2022/10/13 17:01:32 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_bonus.h"
#include "error_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_path_list	path_list;
	t_pipe		pipe_tool;

	if (argc < 5)
		invalid_argument();
	parse_path(envp, &path_list);
	init_pipe_tool(&pipe_tool, argc, argv);
	pipex(&pipe_tool, &path_list);
	delete_path_list(&path_list);
	return (0);
}
