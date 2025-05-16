/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:36 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/15 11:32:11 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/* 
int	main(int c, char **args)
{
	t_Vector3 ray_origin = {0, 0, 0};
	t_Vector3 ray_dir = vector_normalize((t_Vector3){0, 0, 1});

	t_cyl_prop cyl;
	cyl.pos = (t_Vector3){0, 0, 5};
	cyl.rot = vector_normalize((t_Vector3){1, 1, 1}); // diagonal cylinder
	cyl.radius = 1.0f;
	cyl.height = 4.0f;

	float t;
	if (ray_cylinder_intersect(ray_origin, ray_dir, cyl, &t)) {
		printf("Intersection at t = %f\n", t);
	} else {
		printf("No intersection\n");
	}
	return 0;
}
 */
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