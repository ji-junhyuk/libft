/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:15:47 by junji             #+#    #+#             */
/*   Updated: 2022/10/26 16:22:47 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_bonus.h"
#include "error_bonus.h"
#include "define_bonus.h"
#include <stdlib.h>

t_point	*get_point(int x, int y, t_tool *tool)
{
	t_point	*point;
	int		idx;

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		put_error("get_point malloc");
	point->x = x;
	point->y = y;
	idx = tool->horizental * y + x;
	point->z = tool->height[idx];
	if (tool->color[idx] == 0)
		point->color = 0xFFFFFF;
	else
		point->color = tool->color[idx];
	return (point);
}

void	convert_isometric(int *x, int *y, int *z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(M_PI / 60 * 4) - prev_y * cos(M_PI / 60 * 4);
	*y = prev_x * sin(M_PI / 60 * 4) + prev_y * sin(M_PI / 60 * 4) - *z;
}

t_point	*projection(t_point *point, t_tool *tool)
{
	point->x *= tool->offset;
	point->y *= tool->offset;
	point->z *= tool->offset;
	point->z /= tool->modify_z;
	point->x -= (tool->horizental * tool->offset) / 2;
	point->y -= (tool->vertical * tool->offset) / 2;
	rotate_x(&(point->y), &(point->z), tool->angle_x);
	rotate_y(&(point->x), &(point->z), tool->angle_y);
	rotate_z(&(point->x), &(point->y), tool->angle_z);
	if (tool->isometric == 1)
		convert_isometric(&(point->x), &(point->y), &(point->z));
	point->x += WINDOW_HORIZENTAL / 2 + tool->offset_x;
	point->y += WINDOW_VERTICAL / 2 + tool->offset_y;
	point->y += tool->vertical * tool->offset / 2;
	return (point);
}

void	init_delta_step(t_point *delta,
		t_point *start, t_point *end, t_point *step)
{
	delta->x = abs(end->x - start->x);
	delta->y = -abs(end->y - start->y);
	if (start->x < end->x)
		step->x = 1;
	else
		step->x = -1;
	if (start->y < end->y)
		step->y = 1;
	else
		step->y = -1;
}

void	plot_line(t_point *start, t_point *end, t_tool *tool)
{
	t_point	delta;
	t_point	*cur;
	t_point	step;
	int		error[2];

	init_delta_step(&delta, start, end, &step);
	error[0] = delta.x + delta.y;
	cur = start;
	while (!(cur->x == end->x && cur->y == end->y))
	{
		my_mlx_pixel_put(cur, tool);
		error[1] = 2 * error[0];
		if (error[1] >= delta.y)
		{
			error[0] += delta.y;
			cur->x += step.x;
		}
		if (error[1] <= delta.x)
		{
			error[0] += delta.x;
			cur->y += step.y;
		}
	}
	free(start);
	free(end);
}
