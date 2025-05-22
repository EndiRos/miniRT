#include "MLX42/MLX42.h"
#include "minirt.h"



int main (int argc, char **argv)
{
	mlx_t       *mlx;
    mlx_image_t *image;

	(void) argc;
	(void) argv; 
	if (!(mlx = mlx_init(1600, 1200, "tXuperRT", true)))
	{
		perror (mlx_strerror(mlx_errno));
		return(1);
	}
	
	if (!(image = mlx_new_image(mlx, 1600, 1200)))
	{
		mlx_close_window(mlx);
		perror (mlx_strerror(mlx_errno));
		return(1);
	}
	calculate_image(image);
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		perror (mlx_strerror(mlx_errno));
		return(1);
	}
	

	mlx_loop(mlx);
	key_hook(mlx)
	mlx_terminate(mlx);
	return (0);
}