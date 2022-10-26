/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:07:58 by junji             #+#    #+#             */
/*   Updated: 2022/10/26 16:10:35 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "define_bonus.h"
#include "mlx.h"
#include <stdlib.h>

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
	else if (keycode == R || keycode == T)
		depth(keycode, tool);
	drawing(tool);
	return (0);
}
