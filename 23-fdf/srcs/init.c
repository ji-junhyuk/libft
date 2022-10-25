/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 09:35:04 by junji             #+#    #+#             */
/*   Updated: 2022/10/25 22:25:18 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "error.h"
#include "define.h"

#include <stdio.h>
void	init_mlx(t_tool *tool)
{
	tool->mlx = mlx_init();
	if (!tool->mlx)
		put_error("init_mlx mlx_init");			
	tool->mlx_win = mlx_new_window(tool->mlx, WINDOW_HORIZENTAL, WINDOW_VERTICAL, "FDF");
	if (!tool->mlx_win)
		put_error("init_mlx mlx_new_window");
	tool->image = mlx_new_image(tool->mlx, IMAGE_HORIZENTAL, IMAGE_VERTICAL);
	if (!tool->image)
		put_error("init_mlx mlx_new_image");
	tool->addr = mlx_get_data_addr(tool->image, &tool->bits_per_pixel, &tool->size_line, &tool->endian);
	tool->offset_x = 0;
	tool->offset_y = 0;
	tool->angle_x = 0;
	tool->angle_y = 0;
	tool->angle_z = 0;
}
