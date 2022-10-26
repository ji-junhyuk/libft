/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:19:01 by junji             #+#    #+#             */
/*   Updated: 2022/10/26 15:05:27 by junji            ###   ########.fr       */
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

	double				offset;
	double				angle_x;
	double				angle_y;
	double				angle_z;
	int					isometric;

	int					horizental;
	int					vertical;
	int					*height;
	unsigned int		*color;

	int					offset_x;
	int					offset_y;
	int					x;
	int					y;
//	double				z_modify;
}						t_tool;

void	init_mlx(t_tool *tool);
char	**ft_split(char const *str, char c);
int		count_word(const char *str, char c);
char	**free_arr(char **str);
void	drawing(t_tool *tool);
int		key_hook(int keycode, t_tool *tool);

#endif
