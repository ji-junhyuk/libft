/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:13:52 by junji             #+#    #+#             */
/*   Updated: 2022/10/26 16:10:15 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "error_bonus.h"
#include "define_bonus.h"
#include "draw_bonus.h"
#include "mlx.h"
#include <stdlib.h>

void	my_mlx_pixel_put(t_point *point, t_tool *tool)
{
	char	*dst;

	if ((point->x >= 0 && point->x < WINDOW_HORIZENTAL)
		&& (point->y >= 0 && point->y < WINDOW_VERTICAL))
	{
		dst = tool->addr + (point->y * tool->size_line
				+ point->x * (tool->bits_per_pixel / 8));
		*((unsigned int *)dst) = point->color;
	}
}

void	put_menu(t_tool *tool)
{
	mlx_string_put(tool->mlx, tool->mlx_win,
		30, 30, 0x00FF00, "Translate: [W, A, S, D]");
	mlx_string_put(tool->mlx, tool->mlx_win,
		30, 60, 0x00FF00, "Rotate: [X:H L, Y:J K, Z: N M");
	mlx_string_put(tool->mlx, tool->mlx_win,
		30, 90, 0x00FF00, "Zoom: [-, +]");
	mlx_string_put(tool->mlx, tool->mlx_win,
		30, 120, 0x00FF00, "View: [P, I]");
}

void	set_mlx_image(t_tool *tool)
{
	if (tool->image)
		mlx_destroy_image(tool->mlx, tool->image);
	tool->image = mlx_new_image(tool->mlx, WINDOW_HORIZENTAL, WINDOW_VERTICAL);
	if (!tool->image)
		put_error("init_mlx mlx_new_image");
	tool->addr = mlx_get_data_addr(tool->image, &tool->bits_per_pixel,
			&tool->size_line, &tool->endian);
}

void	drawing(t_tool *tool)
{
	set_mlx_image(tool);
	tool->y = -1;
	while (++tool->y < tool->vertical)
	{
		tool->x = -1;
		while (++tool->x < tool->horizental)
		{
			my_mlx_pixel_put(projection(
					get_point(tool->x, tool->y, tool), tool), tool);
			if (tool->x < tool->horizental - 1)
				plot_line(projection(
						get_point(tool->x, tool->y, tool), tool),
					projection(
						get_point(tool->x + 1, tool->y, tool), tool), tool);
			if (tool->y < tool->vertical - 1)
				plot_line(projection(get_point(tool->x, tool->y, tool), tool),
					projection(
						get_point(tool->x, tool->y + 1, tool), tool), tool);
		}
	}
	mlx_put_image_to_window(tool->mlx, tool->mlx_win, tool->image, 0, 0);
	put_menu(tool);
}
