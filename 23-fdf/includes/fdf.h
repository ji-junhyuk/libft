/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:19:01 by junji             #+#    #+#             */
/*   Updated: 2022/10/25 19:35:09 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "math.h"

typedef struct s_tool
{
	void				*mlx;
	void				*mlx_win;
	void				*image;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	void				*addr;
}						t_tool;

typedef struct s_draw_info
{
	int					horizental;
	int					vertical;
	int					*height;
	int					offset;
	unsigned int		*color;
	double				angle_x;
	double				angle_y;
	double				angle_z;
}	t_draw_info;

void	init_mlx(t_tool *tool);
char	**ft_split(char const *str, char c);
int		count_word(const char *str, char c);
char	**free_arr(char **str);
void	drawing(t_tool *tool, t_draw_info *dtool);


#endif
