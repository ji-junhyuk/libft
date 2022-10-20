#include "mlx.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "fdf.h"
#include "get_next_line.h"


/*
 * open, read, write, close
◦ malloc, free
◦ perror, strerror
◦ exit
◦ All the functions defined in the math library (-lm and man 3 math)
◦ All the functions defined in the miniLibX library.
 */

typedef struct	s_tool
{
	void	*mlx;
	void	*mlx_win;
	void	*image;
//	int		bits_per_pixel;
//	int		size_line;
//	int		endian;
	char	*file_name;
	int		horizental;
	int		vertical;
	int					*height;
	unsigned int		*color;
}						t_tool;

void	invalid_input()
{
	write(2, "INVALID INPUT\n", 14);
	exit(1);
}

void	find_vertical_horizental(t_tool *tool)
{
	int		fd;
	char	*line;

	fd = open(tool->file_name, O_RDONLY);
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
//	printf("ho:%d\n", tool->horizental);
//	printf("ve:%d\n", tool->vertical);
}

void	malloc_height_color(t_tool *tool)
{
	int	idx;

	tool->height = malloc(sizeof(int *) * (tool->horizental * tool->vertical));
	if (!tool->height)
	{
		perror("malloc_height_color_1");
		exit(1);
	}
	tool->color = malloc(sizeof(unsigned int *) * (tool->horizental * tool->vertical));
	if (!tool->color)
	{
		perror("malloc_height_color_2");
		exit(1);
	}
	idx = -1;
	while (++idx < tool->horizental * tool->vertical)
	{
		tool->height = 0;
		tool->color = 0;
	}
	//	for (int idx = 0; idx < (tool->horizental * tool->vertical); ++idx)
	//		tool->height[idx] = 1;
	//	for (int idx = 0; idx < (tool->horizental * tool->vertical); ++idx)
	//		printf("%d ", tool->height[idx]);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ')
		++str;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while (*str && (*str >= '0' && * str <= '9'))
	{
		result *= 10;
		result += (*str - '0');
		++str;
	}
	return (sign * result);
}

unsigned int	convert_hex_to_int(char *str)
{
	unsigned int	result;
	
//	printf("str:%s\n", str);

	result = 0;
	str += 3;

	return (result);
}

void	find_height_color(t_tool *tool)
{
	int		fd;
	int		idx;
	char	*line;
	char	**number;
	char	**height_color;

//	idx = -1;
//	fd = open(tool->file_name, O_RDONLY);
//	while (1)
//	{
//		line = get_next_line(fd);
//		number = ft_split(line, ' ');
//		while (++idx < tool->horizental)
//		{
//			height_color = ft_split(number[idx], ',');
//			if (ft_strchr(number[idx], ','))
//				tool->color[idx] = convert_hex_to_int(height_color[1]);
//			// ,가 있는 경우 없는 경우.
//			tool->height[idx] = ft_atoi(height_color[0]);
//		}
//		// i < number의 갯수만큼 루프를 돌면서
//		height_color = ft_split(line, ',');
//		// atoi를 해서 height_color[0] -> height[i] 에 넣는다.
//		// 0xFF0000 -> FF0000 -> convert_base 16진수를 10진수로 바꿔서 그 값을 ->color[i]에 넣는다.
//	}
}

void	parse_map_info(t_tool *tool)
{
	find_vertical_horizental(tool);
	malloc_height_color(tool);
	for (int idx = 0; idx < (tool->horizental * tool->vertical); ++idx)
		tool->height[idx] = 1;
	for (int idx = 0; idx < (tool->horizental * tool->vertical); ++idx)
		printf("%d ", tool->height[idx]);
	find_height_color(tool);
}

void	init_tool(t_tool *tool, char *argv[])
{
	tool->file_name = argv[1];
	tool->horizental = 0;
	tool->vertical = 0;
}

int main(int argc, char *argv[])
{
	t_tool	tool;

	init_tool(&tool, argv);
	if (argc != 2)
		invalid_input();
	parse_map_info(&tool);

//	tool.mlx = mlx_init();
//	tool.mlx_win = mlx_new_window(tool.mlx, 1920, 1080, "fdf");
//	tool.image = mlx_new_image(tool.mlx, 500, 500);
//	mlx_put_image_to_window(tool.mlx, tool.mlx_win, tool.image, 500, 500);
//	mlx_loop(tool.mlx);
}
