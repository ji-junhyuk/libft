/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:53:36 by junji             #+#    #+#             */
/*   Updated: 2022/10/26 13:53:54 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "fdf.h"

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	unsigned int	color;
}	t_point;

void	my_mlx_pixel_put(t_point *point, t_tool *tool);
void	rotate_x(int *y, int *z, double angle_x);
void	rotate_y(int *x, int *z, double angle_y);
void	rotate_z(int *x, int *y, double angle_z);
void	plot_line(t_point *start, t_point *end, t_tool *tool);
void	init_delta_step(t_point *delta,
			t_point *start, t_point *end, t_point *step);

t_point	*projection(t_point *point, t_tool *tool);
t_point	*get_point(int x, int y, t_tool *tool);

#endif
