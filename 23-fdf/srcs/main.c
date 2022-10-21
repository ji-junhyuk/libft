#include "mlx.h"
#include "fdf.h"
#include "error.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	size_t			idx;

	idx = -1;
	p = (unsigned char *)b;
	while (++idx < len)
		p[idx] = c;
	return (b);
}

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
//	printf("ho:%d\n", tool->horizental);
//	printf("ve:%d\n", tool->vertical);
}

void	malloc_height_color(t_tool *tool)
{
	int	idx;

	tool->height = malloc(sizeof(int *) * (tool->horizental * tool->vertical));
	if (!tool->height)
		put_error("malloc_height_color malloc1");
	tool->color = malloc(sizeof(unsigned int *) * (tool->horizental * tool->vertical));
	if (!tool->color)
		put_error("malloc_height_color malloc2");
	idx = -1;
	while (++idx < tool->horizental * tool->vertical)
	{
		tool->height[idx] = 0;
		tool->color[idx] = 0;
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

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10); return (c - 'A' + 10);
}

unsigned int	convert_hex_to_int(char *str)
{
	unsigned int	result;
	
	printf("%s\n", str);
	str += 2;
	result = 0;
	while (*str)
	{
		result *= 16;
		result += is_num(*str);
		++str;
	}
	printf("result : %d\n", result);

	return (result);
}

typedef struct s_parse_tool
{
	char	*line;
	char	**height_color_with;
	char	**height_color;
	int		idx;
	int		offset;
}			p_tool;

void	find_height_color(t_tool *tool, int fd)
{
	p_tool ptool;

	memset(&ptool, 0, sizeof(ptool));
	while (1)
	{
		ptool.line = get_next_line(fd);
		if (!ptool.line)
			break ;
		ptool.height_color_with = ft_split(ptool.line, ' ');
		ptool.idx = -1;
		++ptool.offset;
		while (++ptool.idx < tool->horizental)
		{
			ptool.height_color = ft_split(ptool.height_color_with[ptool.idx], ',');
			if (ft_strchr(ptool.height_color_with[ptool.idx], ','))
				tool->color[ptool.idx + ptool.offset * tool->horizental] = convert_hex_to_int(ptool.height_color[1]);
			tool->height[ptool.idx + ptool.offset * tool->horizental] = ft_atoi(ptool.height_color[0]);
			free_arr(ptool.height_color);
		}
		free_arr(ptool.height_color_with);
		free(ptool.line);
	}
}

void	get_line(t_tool *tool)
{
	int		fd;

	fd = open(tool->file_name, O_RDONLY);
	if (fd == -1)
		put_error("find_height_color open");
	find_height_color(tool, fd);
}

void	parse_map_info(t_tool *tool)
{
	find_vertical_horizental(tool);
	malloc_height_color(tool);
	get_line(tool);
}

void	init_tool(t_tool *tool, char *argv[])
{
	tool->file_name = argv[1];
	tool->horizental = 0;
	tool->vertical = 0;
	tool->height = NULL;
	tool->color = NULL;
}

int main(int argc, char *argv[])
{
	t_tool	tool;

	init_tool(&tool, argv);
	if (argc != 2)
		invalid_input();
	parse_map_info(&tool);
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
