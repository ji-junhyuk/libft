/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */ /*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:24:12 by junji             #+#    #+#             */
/*   Updated: 2022/10/26 14:10:08 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "define.h"
#include "mlx.h"
#include <stdlib.h>

void	height(int keycode, t_tool *tool)
{
//	if (keycode == INCREASE_H)
//		tool->z_modify += 0.05;
//	else if (keycode == DECREASE_H)
//		tool->z_modify -= 0.05;
}
void	rotate(int keycode, t_tool *tool)
{
	if (keycode == H)
		tool->angle_x += M_PI / 180.0;
	else if (keycode == L)
		tool->angle_x -= M_PI / 180.0;
	else if (keycode == J)
		tool->angle_y += M_PI / 180.0;
	else if (keycode == K)
		tool->angle_y -= M_PI / 180.0;
	else if (keycode == N)
		tool->angle_z -= M_PI / 180.0;
	else if (keycode == M)
		tool->angle_z += M_PI / 180.0;
}

void	translate(int keycode, t_tool *tool)
{
	if (keycode == W)
		tool->offset_y -= 10;
	else if (keycode == A)
		tool->offset_x -= 10;
	else if (keycode == S)
		tool->offset_y += 10;
	else if (keycode == D)
		tool->offset_x += 10;
}

void	change_angle(int keycode, t_tool *tool)
{
	if (keycode == I)
		tool->isometric = 1;
	else if (keycode == P)
		tool->isometric = 0;
}

void	zoom(int keycode, t_tool *tool)
{
	if (keycode == PLUS)
		tool->offset *= 1.1;
	else if (keycode == MINUS)
		tool->offset /= 1.1;
}

#include <stdio.h>
int	key_hook(int keycode, t_tool *tool)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(tool->mlx, tool->mlx_win);
		free(tool->height);
		free(tool->color);
		exit(0);
	}
	else if (keycode == P || keycode == I)
		change_angle(keycode, tool);
	else if (keycode == J || keycode == K
		|| keycode == H || keycode == L
		|| keycode == N || keycode == M)
		rotate(keycode, tool);
	else if (keycode == W || keycode == A || keycode == S || keycode == D)
		translate(keycode, tool);
	else if (keycode == PLUS || keycode == MINUS)
		zoom(keycode, tool);
	else if (keycode == INCREASE_H || keycode == DECREASE_H)
	{
		printf("keycode: %d\n", keycode);
		height(keycode, tool);
	}
	drawing(tool);
	return (0);
}
