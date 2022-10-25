/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:14:26 by junji             #+#    #+#             */
/*   Updated: 2022/10/25 20:39:57 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "parse.h"
#include "error.h"
#include "utils.h"
#include "utils2.h"
#include "fcntl.h"
#include "define.h"

void	find_vertical_horizental(t_draw_info *dtool, const char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		put_error("find_vertical_horizental open");
	line = get_next_line(fd);
	line[ft_strlen(line) - 1] = 0;
	dtool->horizental = count_word(line, ' ');
	free(line);
	while (1)
	{
		++dtool->vertical;
		line = get_next_line(fd);
		if (!line)
		{
			break ;
			free(line);
		}
		free(line);
	}
	close(fd);
//	printf("ho:%d\n", tool->horizental);
//	printf("ve:%d\n", tool->vertical);
}

void	malloc_height_color(t_draw_info *dtool)
{
	int	idx;

	dtool->height = malloc(sizeof(int *) * (dtool->horizental * dtool->vertical));
	if (!dtool->height)
		put_error("malloc_height_color malloc1");
	dtool->color = malloc(sizeof(unsigned int *)
			* (dtool->horizental * dtool->vertical));
	if (!dtool->color)
		put_error("malloc_height_color malloc2");
	idx = -1;
	while (++idx < dtool->horizental * dtool->vertical)
	{
		dtool->height[idx] = 0;
		dtool->color[idx] = 0;
	}
	//	for (int idx = 0; idx < (tool->horizental * tool->vertical); ++idx)
	//		tool->height[idx] = 1;
	//	for (int idx = 0; idx < (tool->horizental * tool->vertical); ++idx)
	//		printf("%d ", tool->height[idx]);
}

void	find_height_color(t_draw_info *dtool, int fd)
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
		while (++ptool.idx < dtool->horizental)
		{
			ptool.h_c = ft_split(ptool.h_c_with[ptool.idx], ',');
			if (ft_strchr(ptool.h_c_with[ptool.idx], ','))
				dtool->color[ptool.idx + ptool.offset * dtool->horizental]
					= convert_hex_to_int(ptool.h_c[1]);
			dtool->height[ptool.idx + ptool.offset * dtool->horizental]
				= ft_atoi(ptool.h_c[0]);
			free_arr(ptool.h_c);
		}
		free_arr(ptool.h_c_with);
		free(ptool.line);
	}
}

void	get_line(t_draw_info *dtool, const char *file_name)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		put_error("find_height_color open");
	find_height_color(dtool, fd);
}

void	find_offset(t_draw_info *dtool)
{
	double offset_x;
	double offset_y;

	offset_x = IMAGE_HORIZENTAL / 2.0 / dtool->horizental;
	offset_y = IMAGE_VERTICAL / 2.0 / dtool->vertical;
	dtool->offset = (int)fmin(offset_x, offset_y);
	dtool->angle_x = 0;
	dtool->angle_y = 0;
	dtool->angle_z = 0;
}
