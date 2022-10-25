/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:18:06 by junji             #+#    #+#             */
/*   Updated: 2022/10/25 13:30:01 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "fdf.h"

typedef struct s_parse_tool
{
	char	*line;
	char	**h_c_with;
	char	**h_c;
	int		idx;
	int		offset;
}			t_parse_tool;


void			find_vertical_horizental(t_draw_info *dtool, const char *file_name);
void			malloc_height_color(t_draw_info *dtool);
void			get_line(t_draw_info *dtool, const char *file_name);
int				ft_atoi(const char *str);
unsigned int	convert_hex_to_int(const char *str);

void	find_offset(t_draw_info *dtool);
#endif
