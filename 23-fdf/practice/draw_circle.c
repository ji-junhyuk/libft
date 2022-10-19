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

//void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
//{
//	char	*dst;
//
//	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//	*(unsigned int*)dst = color;
//}

void	my_mlx_pixel_put(t_tool *tool, int x, int y, int color)
{

	char	*dst;

	printf(">>>>>>>>>> x: %d y: %d\n", x, y);
	dst = tool->addr + (y * tool->line_length + x * (tool->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
#include <stdio.h>
void DrawCircle(t_tool *tool, int x, int y, int r, int color)
{
      static const double PI = 3.1415926535;
      double i, angle, x1, y1;
	color = 0;
      for (i = 0; i < 360; i += 0.1)
      {
//		  if (i < 50)
//		  {
//			  color = 0x00FF0000;
//		  }
//		  else  if (i < 100)
//		  {
//			  color = 0x00ff8c00;
//		  }
//		  else if (i < 150)
//		  {
//			  color = 0x00ffff00;
//		  }
//		  else if (i < 200)
//		  {
//			  color = 0x008000;
//		  }
//		  else if (i < 250)
//		  {
//			  color = 0x0000ff;
//		  }
//		  else if (i < 300)
//		  {
//			  color = 0x4b0082;
//		  }
//		  else
//		  {
//			  color = 0x800080;
//		  }
			if (color % 56 == 0)
				color <<= 1;
			color++;
			angle = i;

			x1 = r * cos(angle * PI / 180);
			y1 = r * sin(angle * PI / 180);

			printf("x1 : %f, y1 : %f\n", x1, y1);
			printf(": %f\n", angle * PI * 2 / 360);
			my_mlx_pixel_put(tool, x + x1, y + y1, color);
      }
}

int	main(void)
{
	t_tool	tool;

	tool.mlx = mlx_init();
	tool.mlx_win = mlx_new_window(tool.mlx, 1920, 1080, "Hello world!");
	tool.img = mlx_new_image(tool.mlx, 1920, 1080);
	tool.addr = mlx_get_data_addr(tool.img, &tool.bits_per_pixel, &tool.line_length,
								&tool.endian);
	printf("%d\n", tool.line_length);
	printf("%d\n", tool.bits_per_pixel);
	printf("%p\n", tool.img);
	for (int idx = 0; idx < 1000; ++idx)
	{
		my_mlx_pixel_put(&tool, 5, idx, 0x00FF0000);
	}
	DrawCircle(&tool, 500, 500, 500, 0X000000FF);
//	for (int idx = 0; idx < 1000; ++idx)
//	{
//		my_mlx_pixel_put(&tool, 5, idx, 0x000000FF);
////		my_mlx_pixel_put(&img, idx, 10, 0x0000FF00);
////		my_mlx_pixel_put(&img, idx, idx, 0x00FF0000);
////		my_mlx_pixel_put(&img, 7, 7, 0xFF000000);
//	}
		
	mlx_put_image_to_window(tool.mlx, tool.mlx_win, tool.img, 0, 0);
	mlx_loop(tool.mlx);
}
