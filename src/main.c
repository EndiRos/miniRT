/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:36 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/16 13:19:31 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
int	main(int c, char **args)
{
	t_Vector3	ray_origin;
	t_Vector3	ray_dir;
	t_cyl_prop	cyl;
	float		t;

	ray_origin = {0, 0, 0};
	ray_dir = vector_normalize((t_Vector3){0, 0, 1});
	cyl.pos = (t_Vector3){0, 0, 5};
	cyl.rot = vector_normalize((t_Vector3){1, 1, 1});
	cyl.radius = 1.0f;
	cyl.height = 4.0f;
	if (ray_cylinder_intersect(ray_origin, ray_dir, cyl, &t)) {
		printf("Intersection at t = %f\n", t);
	} else {
		printf("No intersection\n");
	}
	return (0);
}
 */
void	key_hook(struct mlx_key_data keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(mlx);
	}
}

unsigned int	get_intersection(t_object *obj, t_Vector3 ray_origin,
		t_Vector3 ray_dir, float *dist)
{
	unsigned int	color;

	color = 0;
	if (obj->obj_type == SPHERE)
		color = ray_sphere_intersect(ray_origin, ray_dir,
				*(t_sphere_prop *)obj->props, dist);
	else if (obj->obj_type == CYLINDER)
		color = ray_cylinder_intersect(ray_origin, ray_dir,
				*(t_cyl_prop *)obj->props, dist);
	else if (obj->obj_type == PLANE)
		color = ray_plane_intersect(ray_origin, ray_dir,
				*(t_plane_prop *)obj->props, dist);
	return (color);
}

int	check_coll(float px, float py, t_scene *escena, t_object	*obj)
{
	t_Vector3		ray_dir;
	float			min_dist;
	unsigned int	min_color;
	float			temp_dist;
	unsigned int	temp_color;

	ray_dir = vector_normalize((t_Vector3){px, py, 1});
	min_dist = FLT_MAX;
	min_color = 0;
	while (obj)
	{
		temp_dist = FLT_MAX;
		temp_color = get_intersection(obj, escena->cam->pos, ray_dir,
				&temp_dist);
		if (temp_dist < min_dist)
		{
			min_dist = temp_dist;
			min_color = temp_color;
		}
		obj = obj->next;
	}
	return (min_color);
}

void	calculate_image(mlx_image_t *image, t_scene *escena)
{
    unsigned int	px;
	unsigned int	py;
	unsigned int	color;
	float			px_camera;
	float			py_camera;

	px = 0;
	py = 0;
	escena->cam->aspect_ratio = (float)image->width / (float)image->height;
    escena->cam->fov = escena->cam->fov * (M_PI / 180.0f);
    escena->cam->scale = tanf(escena->cam->fov / 2.0f);
    while (py < image->height)
    {
        while (px < image->width)
        {
            px_camera = (2.0f * (px + 0.5f) / image->width - 1.0f) * escena->cam->aspect_ratio * escena->cam->scale;
        	py_camera = (1.0f - 2.0f * (py + 0.5f) / image->height) * escena->cam->scale;

            color = check_coll(px_camera, py_camera, escena, escena->objects);
            mlx_put_pixel(image, px++, py, color);
        }
		px = 0;
		py++;
    }
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_scene		*escena;

	escena = harcoding();
	(void)argc;
	(void)argv;
	if (!(mlx = mlx_init(1600, 1200, "tXuperRT", true)))
	{
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	if (!(image = mlx_new_image(mlx, 1600, 1200)))
	{
		mlx_close_window(mlx);
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	calculate_image(image, escena);
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
