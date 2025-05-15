/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:36 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/15 13:55:07 by imugica-         ###   ########.fr       */
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
void	key_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
	}
}
int	check_coll(float px, float py, t_scene *escena)
{
	t_Vector3		ray_origin;
	t_Vector3		ray_dir;
	float			dist;
	float			min_dist;
	unsigned int	color;
	t_object		*obj;
	unsigned int	min_color;
	float			temp_dist;
	unsigned int	temp_color;

	dist = FLT_MAX;
	min_dist = dist;
	ray_origin = escena->cam->pos;
	ray_dir = vector_normalize((t_Vector3){px, py, 1});
	color = 0;
	min_color = 0;
	obj = escena->objects;
	while (obj)
	{
		temp_dist = FLT_MAX;
		temp_color = 0;
		if (obj->obj_type == SPHERE)
			temp_color = ray_sphere_intersect(ray_origin, ray_dir,
					*(t_sphere_prop *)obj->props, &temp_dist);
		else if (obj->obj_type == CYLINDER)
			temp_color = ray_cylinder_intersect(ray_origin, ray_dir,
					*(t_cyl_prop *)obj->props, &temp_dist);
		else if (obj->obj_type == PLANE)
			temp_color = ray_plane_intersect(ray_origin, ray_dir,
					*(t_plane_prop *)obj->props, &temp_dist);
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
	float			screen_x;
	float			screen_y;
	unsigned int	px;
	unsigned int	py;

	px = 0;
	py = 0;
	while (py < image->height)
	{
		while (px < image->width)
		{
			screen_x = (2.0f * px) / image->width - 1.0f;
			screen_y = 1.0f - (2.0f * py) / image->height;
			mlx_put_pixel(image, px, py, check_coll(screen_x, screen_y,
					escena));
			px++;
		}
		px = 0;
		py++;
	}
}

/*
void calculate_image(mlx_image_t *image, t_scene *escena)
{
    float aspect_ratio = (float)image->width / (float)image->height;
    float fov_rad = escena->cam->fov * (M_PI / 180.0f);
    float scale = tanf(fov_rad / 2.0f);

    unsigned int px, py;

    for (py = 0; py < image->height; py++)
    {
        for (px = 0; px < image->width; px++)
        {
            float px_ndc = (px + 0.5f) / image->width;
            float py_ndc = (py + 0.5f) / image->height;

            float px_camera = (2.0f * px_ndc - 1.0f) * aspect_ratio * scale;
            float py_camera = (1.0f - 2.0f * py_ndc) * scale;

            unsigned int color = check_coll(px_camera, py_camera, escena);
            mlx_put_pixel(image, px, py, color);
        }
    }
}*/

int	main(int argc, char **argv)
{
	mlx_t *mlx;
	mlx_image_t *image;
	t_scene *escena;

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
	mlx_loop(mlx);
	key_hook(mlx);
	mlx_terminate(mlx);
	return (0);
}