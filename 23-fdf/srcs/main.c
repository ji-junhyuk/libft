/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:03:11 by junji             #+#    #+#             */
/*   Updated: 2022/10/21 16:07:34 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "parse.h"
#include "error.h"
#include <stdlib.h>
//#include "fdf.h"
//#include "error.h"
//#include <errno.h>
//#include <string.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include "utils.h"
//#include "utils2.h"

void	parse_map_info(t_tool *tool, const char *file_name)
{
	find_vertical_horizental(tool, file_name);
	malloc_height_color(tool);
	get_line(tool, file_name);
	free(tool->height);
	free(tool->color);
}

void			my_mlx_pixel_put(t_tool *tool, int x, int y, int color)
{
	char	*dst;

	dst = tool->addr + (y * tool->line_length + x * (tool->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_tool *tool)
{
	if (keycode == 53)
	{
		mlx_destroy_window(tool->mlx, tool->mlx_win);
		exit(0);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_tool	tool;

	if (argc != 2)
		invalid_input();
	parse_map_info(&tool, argv[1]);
//	for (int idx = 0; idx < tool.horizental * tool.vertical; ++idx)
//	{
//		printf("tool.height[%d]: %d\n", idx,tool.height[idx]);
//	}
//	for (int idx = 0; idx < tool.horizental * tool.vertical; ++idx)
//	{
//		printf("tool.color[%d]: %d\n", idx,tool.color[idx]);
//}
	tool.mlx = mlx_init();
	tool.mlx_win = mlx_new_window(tool.mlx, 1920, 1080, "fdf");
	tool.image = mlx_new_image(tool.mlx, 1920, 1080);
	tool.addr = mlx_get_data_addr(tool.image, &tool.bits_per_pixel, &tool.line_length, &tool.endian);
//	for (int idx = 0; idx < 1000; ++idx)
//	{
//	}
//		my_mlx_pixel_put(&tool, 500, idx, 0x00ff0000); 	

	mlx_put_image_to_window(tool.mlx, tool.mlx_win, tool.image, 500, 500);
	mlx_key_hook(tool.mlx_win, key_hook, &tool);
	mlx_loop(tool.mlx);
}
