/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@42seoul.student.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:03:11 by junji             #+#    #+#             */
/*   Updated: 2022/10/21 14:47:29 by junji            ###   ########.fr       */
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
	free(tool.height);
	free(tool.color);
//	tool.mlx = mlx_init();
//	tool.mlx_win = mlx_new_window(tool.mlx, 1920, 1080, "fdf");
//	tool.image = mlx_new_image(tool.mlx, 500, 500);
//	mlx_put_image_to_window(tool.mlx, tool.mlx_win, tool.image, 500, 500);
//	mlx_loop(tool.mlx);
}
