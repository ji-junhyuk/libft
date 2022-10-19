#include "MLX/mlx.h"

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 5120, 2880, "Hello world!"); // width, height
	mlx_loop(mlx);
}
