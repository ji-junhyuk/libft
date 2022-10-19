#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <mlx.h>
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
}				t_tool;

void	my_mlx_pixel_put(t_tool *tool, int x, int y, int color)
{
	char	*dst;

	dst = tool->addr + (y * tool->line_length + x * (tool->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void DrawCircle(t_tool *tool, int x, int y, int r, int color)
{
      	static const double PI = 3.1415926535;
      	double i, angle, x1, y1;

	  	color = 0X00FF0000;
		for (int idx = 0; idx < 360; ++idx)
		{
			angle = idx;
			x1 = r * cos(angle * PI / 180);
			y1 = r * sin(angle * PI / 180);
			my_mlx_pixel_put(tool, x + x1, y + y1, color);
		}
}

int	hello(int keycode, t_tool *tool)
{
	if (keycode == 1)
	{
		for (int idx = 0; idx < 500; ++idx)
			my_mlx_pixel_put(tool, 50, 50 + idx, 0x000000FF);
	}
	if (keycode == 2)
		DrawCircle(tool, 700, 700, 100, 0X00000000);
	mlx_put_image_to_window(tool->mlx, tool->mlx_win, tool->img, 0, 0);
	printf("Hello keycode: %d\n", keycode);
	return (0);
}

int	main(void)
{
	t_tool	tool;

	tool.mlx = mlx_init();
	tool.mlx_win = mlx_new_window(tool.mlx, 1920, 1080, "Hello world!");
	tool.img = mlx_new_image(tool.mlx, 1920, 1080);
	tool.addr = mlx_get_data_addr(tool.img, &tool.bits_per_pixel, &tool.line_length,
								&tool.endian);
	DrawCircle(&tool, 700, 700, 100, 0X00000000);
	mlx_put_image_to_window(tool.mlx, tool.mlx_win, tool.img, 0, 0);

	mlx_key_hook(tool.mlx_win, hello, &tool);
	mlx_loop(tool.mlx);
}
