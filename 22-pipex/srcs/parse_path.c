/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:12:30 by junji             #+#    #+#             */
/*   Updated: 2022/10/13 17:00:15 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "string_utils.h"
#include "error.h"

void	insert_path_list(t_path_list *list, char *path)
{
	t_path_node		*node;

	node = malloc(sizeof(t_path_node));
	if (!node)
	{
		perror("insert_path malloc");
		exit(1);
	}
	node->path = ft_strdup(path);
	++list->cnt;
	if (list->tail == NULL)
	{	
		list->tail = node;
		list->head = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
}

void	parse_path(char *envp[], t_path_list *path_list)
{
	int		idx;
	int		jdx;
	char	**path;

	idx = -1;
	init_path_list(path_list);
	while (envp[++idx])
	{
		if (ft_strncmp(envp[idx], "PATH", 4) == 0)
		{
			path = ft_split(&envp[idx][5], ':');
			jdx = -1;
			while (path[++jdx])
				insert_path_list(path_list, path[jdx]);
			free_arr(path);
		}
		if (ft_strncmp(envp[idx], "PWD", 3) == 0)
		{
			path = ft_split(&envp[idx][5], ':');
			jdx = -1;
			while (path[++jdx])
				insert_path_list(path_list, path[jdx]);
			free_arr(path);
		}
	}
}
