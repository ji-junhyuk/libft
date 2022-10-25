/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:13:52 by junji             #+#    #+#             */
/*   Updated: 2022/10/25 22:36:52 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "error.h"
#include "define.h"
#include <stdlib.h>
#include "mlx.h"

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	unsigned int	color;
}	t_point;

void	rotate_x(int *y, int *z, double angle_x)
{
	int	prev_y;
	int	prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = cos(angle_x) * prev_y - sin(angle_x) * prev_z;
	*z = sin(angle_x) * prev_y + cos(angle_x) * prev_z;
}

void	rotate_y(int *x, int *z, double angle_y)
{
	int	prev_x;
	int	prev_z;

	prev_x = *x;
	prev_z = *z;
	*x = cos(angle_y) * prev_x + sin(angle_y) * prev_z;
	*z = -sin(angle_y) * prev_x + cos(angle_y) * prev_z;
}

void	rotate_z(int *x, int *y, double angle_z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = cos(angle_z) * prev_x - sin(angle_z) * prev_y;
	*y = sin(angle_z) * prev_x + cos(angle_z) * prev_y;
}

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

static void	convert_isometric(int *x, int *y, int *z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(M_PI / 60 * 4) - prev_y * cos(M_PI / 60 * 4);
	*y = prev_x * sin(M_PI / 60 * 4) + prev_y * sin(M_PI / 60 * 4) - *z;
}

static t_point	*project_point(t_point *point, t_tool *tool)
{
	point->x *= tool->offset;
	point->y *= tool->offset;
	point->z *= tool->offset;
	point->x -= (tool->horizental * tool->offset) / 2;
	point->y -= (tool->vertical * tool->offset) / 2;
	rotate_x(&(point->y), &(point->z), tool->angle_x);
	rotate_y(&(point->x), &(point->z), tool->angle_y);
	rotate_z(&(point->x), &(point->y), tool->angle_z);
	convert_isometric(&(point->x), &(point->y), &(point->z));
	point->x += IMAGE_HORIZENTAL / 2;
	point->y += IMAGE_VERTICAL / 2;
	point->y += tool->vertical * tool->offset / 2;
	return (point);
}

static void	init_delta_step(t_point *delta, t_point *start, t_point *end, t_point *step)
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

static void	my_mlx_pixel_put(t_point *point, t_tool *tool)
{
	char	*dst;

	if ((point->x >= 0 && point->x < IMAGE_HORIZENTAL) && (point->y >= 0 && point->y < IMAGE_VERTICAL))
	{
		dst = tool->addr + (point->y * tool->size_line + point->x * (tool->bits_per_pixel / 8));
		*((unsigned int *)dst) = point->color;
	}
}

static void	plot_line(t_point *start, t_point *end, t_tool *tool)
{
	t_point	delta;
	t_point	*cur;
	t_point	step;
	int		error[2];

	init_delta_step(&delta, start, end, &step);
	error[0] = delta.x + delta.y;
	cur = start;
	while (1)
	{
		my_mlx_pixel_put(cur, tool);
		if (cur->x == end->x && cur->y == end->y)
			break ;
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

void	drawing(t_tool *tool)
{
	int	x;
	int	y;

	if (tool->image)
		mlx_destroy_image(tool->mlx, tool->image);
	tool->image = mlx_new_image(tool->mlx, WINDOW_HORIZENTAL, WINDOW_VERTICAL);
	tool->addr = mlx_get_data_addr(tool->image, &tool->bits_per_pixel, &tool->size_line, &tool->endian);
	y = -1;
	while (++y < tool->vertical)
	{
		x = -1;
		while (++x < tool->horizental)
		{
			my_mlx_pixel_put(project_point(get_point(x, y, tool), tool), tool);
			if (x < tool->horizental - 1)
				plot_line(project_point(get_point(x, y, tool), tool), project_point(get_point(x + 1, y, tool), tool), tool);
			if (y < tool->vertical - 1)
				plot_line(project_point(get_point(x, y, tool), tool), project_point(get_point(x, y + 1, tool), tool), tool);
		}
	}
	mlx_put_image_to_window(tool->mlx, tool->mlx_win, tool->image, 0, 0);
	free(tool->height);
	free(tool->color);
}
