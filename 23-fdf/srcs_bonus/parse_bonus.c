/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:14:26 by junji             #+#    #+#             */
/*   Updated: 2022/10/26 16:11:35 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include "parse_bonus.h"
#include "error_bonus.h"
#include "utils_bonus.h"
#include "utils2_bonus.h"
#include "define_bonus.h"
#include <fcntl.h>

void	find_vertical_horizental(t_tool *tool, const char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		put_error("find_vertical_horizental open");
	line = get_next_line(fd);
	line[ft_strlen(line) - 1] = 0;
	tool->horizental = count_word(line, ' ');
	free(line);
	while (1)
	{
		++tool->vertical;
		line = get_next_line(fd);
		if (!line)
		{
			break ;
			free(line);
		}
		free(line);
	}
	close(fd);
}

void	malloc_height_color(t_tool *tool)
{
	int	idx;

	tool->height = malloc(sizeof(int *) * (tool->horizental * tool->vertical));
	if (!tool->height)
		put_error("malloc_height_color malloc1");
	tool->color = malloc(sizeof(unsigned int *)
			* (tool->horizental * tool->vertical));
	if (!tool->color)
		put_error("malloc_height_color malloc2");
	idx = -1;
	while (++idx < tool->horizental * tool->vertical)
	{
		tool->height[idx] = 0;
		tool->color[idx] = 0;
	}
}

void	find_height_color(t_tool *tool, int fd)
{
	t_parse_tool	ptool;

	ft_memset(&ptool, 0, sizeof(ptool));
	ptool.offset = -1;
	while (1)
	{
		ptool.line = get_next_line(fd);
		if (!ptool.line)
			break ;
		ptool.h_c_with = ft_split(ptool.line, ' ');
		ptool.idx = -1;
		++ptool.offset;
		while (++ptool.idx < tool->horizental)
		{
			ptool.h_c = ft_split(ptool.h_c_with[ptool.idx], ',');
			if (ft_strchr(ptool.h_c_with[ptool.idx], ','))
				tool->color[ptool.idx + ptool.offset * tool->horizental]
					= convert_hex_to_int(ptool.h_c[1]);
			tool->height[ptool.idx + ptool.offset * tool->horizental]
				= ft_atoi(ptool.h_c[0]);
			free_arr(ptool.h_c);
		}
		free_arr(ptool.h_c_with);
		free(ptool.line);
	}
}

void	get_line(t_tool *tool, const char *file_name)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		put_error("find_height_color open");
	find_height_color(tool, fd);
}

void	find_offset(t_tool *tool)
{
	double	offset_x;
	double	offset_y;

	offset_x = WINDOW_HORIZENTAL / 2.0 / tool->horizental;
	offset_y = WINDOW_VERTICAL / 2.0 / tool->vertical;
	tool->offset = fmin(offset_x, offset_y);
	tool->angle_x = 0;
	tool->angle_y = 0;
	tool->angle_z = 0;
}
