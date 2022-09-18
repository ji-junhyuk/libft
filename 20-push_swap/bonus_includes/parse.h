/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:04:22 by junji             #+#    #+#             */
/*   Updated: 2022/09/18 09:22:48 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "checker.h"
# include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len);
int		count_word(char *str);
char	**ft_split(char *str);

int		insert_list(t_list *list, int number);
void	free_arr(char **copy, int idx);
int		free_split(char **copy, int idx);

#endif
