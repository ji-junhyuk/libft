#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "../MLX42/include/MLX42/MLX42.h"
#define WIDTH 5120
#define HEIGHT 2880

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;


	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int32_t	main(void)
{
	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();

	// Create a new image
	mlx_image_t* img = mlx_new_image(mlx, 5, 5);
	if (!img)
		error();

	// Set every pixel to white
	memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));

	img->instances[0].x += 5;
	img->instances[0].y += 5;
	// Display an instance of the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);

	// Optional, terminate will clean up any left overs, this is just to demonstrate.
	
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
