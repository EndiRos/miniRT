/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:40:45 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/26 14:28:16 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	shade(t_Intersection inter, t_Vector3 ray_dir, t_scene *escena,
	int light)
{
t_shade	shading;

shading.hit_point = vector_add(*escena->cam->pos, vector_scale(ray_dir,
			inter.min_dist));
shading.normal = vector_normalize((t_Vector3){0, 0, 1});
if (inter.object->obj_type == SPHERE)
	shading.normal = vector_normalize(sphere_normal((t_sphere_prop *)inter.object->props,
				shading.hit_point));
else if (inter.object->obj_type == PLANE)
	shading.normal = vector_normalize(plane_normal((t_plane_prop *)inter.object->props));
else if (inter.object->obj_type == CYLINDER)
	shading.normal = vector_normalize(cylinder_normal((t_cyl_prop *)inter.object->props,
				shading.hit_point));
// compute_color(shading);
return (compute_color(escena, shading, inter, light));
}

t_Vector3 create_cam_ray(float px_camera, float py_camera, t_scene *escena)
{
    t_Vector3 cam_forward = *escena->cam->rot;
    t_Vector3 world_up = {0.0f, 1.0f, 0.0f};
    t_Vector3 cam_right = vector_normalize(vector_cross(world_up, cam_forward));
    t_Vector3 cam_up = vector_cross(cam_forward, cam_right);

    t_Vector3 ray_cam_dir = {
        px_camera * escena->cam->aspect_ratio * escena->cam->scale,
        py_camera * escena->cam->scale,
        1.0f
    };

    t_Vector3 ray_world_dir = vector_normalize(
        vector_add(
            vector_add(
                vector_scale(cam_right, ray_cam_dir.x),
                vector_scale(cam_up, ray_cam_dir.y)
            ),
            vector_scale(cam_forward, ray_cam_dir.z)
        )
    );

    return ray_world_dir;
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
	while (py < image->height)
	{
		while (px < image->width)
		{
			px_camera = (2.0f * (px + 0.5f) / image->width - 1.0f);
			py_camera = (1.0f - 2.0f * (py + 0.5f) / image->height);
			color = check_coll(create_cam_ray(px_camera, py_camera, escena),
					escena, escena->objects);
			mlx_put_pixel(image, px++, py, color);
		}
		px = 0;
		py++;
	}
}
