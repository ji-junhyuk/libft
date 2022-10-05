/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:32:24 by junji             #+#    #+#             */
/*   Updated: 2022/10/05 17:49:33 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_cmd_node
{
	char				**cmd;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_cmd_list
{
	t_cmd_node	*tail;
	t_cmd_node	*head;
	int			cnt;
}	t_cmd_list;

typedef struct s_path_node
{
	char				*path;
	struct s_path_node	*next;
}	t_path_node;

typedef struct s_path_list
{
	t_path_node	*tail;
	t_path_node	*head;
	int			cnt;
}	t_path_list;

char	**ft_split(char const *str, char c);
char	*ft_strdup(const char *src);
void	init_path_list(t_path_list *list);
void	init_cmd_list(t_cmd_list *list);
void	free_arr(char **arr);

#endif
