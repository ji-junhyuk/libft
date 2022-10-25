/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */ /*   Created: 2022/10/21 14:03:11 by junji             #+#    #+#             */
/*   Updated: 2022/10/25 18:46:23 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "parse.h"
#include "error.h"
#include <stdlib.h>

void	parse_map_info(t_draw_info *dtool, const char *file_name) {
	find_vertical_horizental(dtool, file_name);
	malloc_height_color(dtool);
	get_line(dtool, file_name);
	find_offset(dtool);
}


int	key_hook(int keycode, t_tool *tool)
{
	if (keycode == 53)
	{
		mlx_destroy_window(tool->mlx, tool->mlx_win);
//		free(dtool.height);
//		free(dtool.color);
		exit(0);
	}
	return (0);
}

#include <stdio.h>
int	main(int argc, char *argv[])
{
	t_tool			tool;
	t_draw_info		dtool;

	if (argc != 2)
		invalid_input();
	parse_map_info(&dtool, argv[1]);
	init_mlx(&tool);
	drawing(&tool, &dtool);
	mlx_key_hook(tool.mlx_win, key_hook, &tool);
	mlx_loop(tool.mlx);
	free(dtool.height);
	free(dtool.color);
}
