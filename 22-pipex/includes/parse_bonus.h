/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:32:24 by junji             #+#    #+#             */
/*   Updated: 2022/10/12 08:26:10 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

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
void	free_arr(char **arr);

#endif
