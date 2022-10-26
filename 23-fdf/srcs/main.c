/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:27:43 by junji             #+#    #+#             */
/*   Updated: 2022/10/26 16:36:32 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "parse.h"
#include "error.h"
#include "define.h"
#include <stdlib.h>

void	init_mlx(t_tool *tool)
{
	tool->mlx = mlx_init();
	if (!tool->mlx)
		put_error("init_mlx mlx_init");
	tool->mlx_win = mlx_new_window(tool->mlx,
			WINDOW_HORIZENTAL, WINDOW_VERTICAL, "FDF");
	if (!tool->mlx_win)
		put_error("init_mlx mlx_new_window");
	tool->offset_x = 0;
	tool->offset_y = 0;
	tool->angle_x = 0;
	tool->angle_y = 0;
	tool->angle_z = 0;
	tool->image = 0;
	tool->isometric = 1;
	tool->modify_z = 1;
}

void	parse_map_info(t_tool *tool, const char *file_name)
{
	find_vertical_horizental(tool, file_name);
	malloc_height_color(tool);
	get_line(tool, file_name);
	find_offset(tool);
}

int	main(int argc, char *argv[])
{
	t_tool			tool;

	if (argc != 2)
		invalid_input();
	parse_map_info(&tool, argv[1]);
	init_mlx(&tool);
	drawing(&tool);
	mlx_key_hook(tool.mlx_win, key_hook, &tool);
	mlx_loop(tool.mlx);
	return (0);
}
