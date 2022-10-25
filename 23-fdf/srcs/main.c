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

void	parse_map_info(t_tool *tool, const char *file_name)
{
	find_vertical_horizental(tool, file_name);
	malloc_height_color(tool);
	get_line(tool, file_name);
	find_offset(tool);
}

typedef enum e_key
{
	P = 35, 
	X = 7,
	Z = 6,
	Y = 16,
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	UP = 126,
	DOWN = 125,
	LEFT = 124,
	RIGHT = 123,
	ESC	= 53
}	t_key;

void	rotate(int keycode, t_tool *tool)
{
	if (keycode == UP)
		tool->angle_x += M_PI / 180.0;
	else if (keycode == DOWN)
		tool->angle_x -= M_PI / 180.0;
	else if (keycode == LEFT)
		tool->angle_y += M_PI / 180.0;
	else if (keycode == RIGHT)
		tool->angle_y -= M_PI / 180.0;
	drawing(tool);
}

void	translate(int keycode, t_tool *tool)
{
	if (keycode == W)
		tool->offset_y += 10;
	else if (keycode == A)
		tool->offset_x -= 10;
	else if (keycode == S)
		tool->offset_y -= 10;
	else if (keycode == D)
		tool->offset_x += 10;
	drawing(tool);
}

#include <stdio.h>
int	key_hook(int keycode, t_tool *tool)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(tool->mlx, tool->mlx_win);
		exit(0);
	}
	else if (keycode == P)
	{
		printf("P\n");
		// isolation X
	}
	else if (keycode == X || keycode == Y || keycode == Z)
	{
		printf("X Y Z\n");
		rotate(keycode, tool);
	}
	else if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
	{
		printf(" UP DOWN LEFT RIGHT\n");
		translate(keycode, tool);
	}
	return (0);
}

#include <stdio.h>
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
