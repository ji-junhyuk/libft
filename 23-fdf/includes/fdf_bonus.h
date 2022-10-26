/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:19:01 by junji             #+#    #+#             */
/*   Updated: 2022/10/26 16:32:04 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

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

	double				angle_x;
	double				angle_y;
	double				angle_z;
	double				offset;
	double				modify_z;
	int					isometric;
	int					offset_x;
	int					offset_y;

	int					horizental;
	int					vertical;
	int					*height;
	unsigned int		*color;

	int					x;
	int					y;
}						t_tool;

void	init_mlx(t_tool *tool);
char	**ft_split(char const *str, char c);
int		count_word(const char *str, char c);
char	**free_arr(char **str);
void	drawing(t_tool *tool);
int		key_hook(int keycode, t_tool *tool);
void	depth(int keycode, t_tool *tool);

#endif
