/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:40:45 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/27 12:07:30 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	shade(t_Intersection in, t_Vector3 ray_dir, t_scene *escena,
		int light)
{
	t_shade	s;

	s.hit_point = vector_add(*escena->cam->pos, vector_scale(ray_dir,
				in.min_dist));
	s.normal = vector_normalize((t_Vector3){0, 0, 1});
	if (in.object->obj_type == SPHERE)
		s.normal = (sphere_normal((t_sphere_prop *)in.object->props,
					s.hit_point));
	else if (in.object->obj_type == PLANE)
		s.normal = (plane_normal((t_plane_prop *)in.object->props));
	else if (in.object->obj_type == CYLINDER)
		s.normal = (cylinder_normal((t_cyl_prop *)in.object->props,
					s.hit_point));
	s.normal = vector_normalize(s.normal);
	return (compute_color(escena, s, in, light));
}

t_Vector3	create_cam_ray(float px_camera, float py_camera, t_scene *escena)
{
	t_Vector3	world_up;
	t_Vector3	cam_right;
	t_Vector3	cam_up;
	t_Vector3	ray_cam_dir;
	t_Vector3	ray_world_dir;

	world_up = (t_Vector3){0.0f, 1.0f, 0.0f};
	cam_right = vector_normalize(vector_cross(world_up, *escena->cam->rot));
	cam_up = vector_cross(*escena->cam->rot, cam_right);
	ray_cam_dir = (t_Vector3){px_camera * escena->cam->aspect_ratio
		* escena->cam->scale, py_camera * escena->cam->scale, 1.0f};
	ray_world_dir = (vector_add(vector_add(vector_scale(cam_right,
						ray_cam_dir.x), vector_scale(cam_up, ray_cam_dir.y)),
				vector_scale(*escena->cam->rot, ray_cam_dir.z)));
	return (vector_normalize(ray_world_dir));
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
