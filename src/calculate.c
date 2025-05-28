/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:40:45 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/28 13:19:30 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	set_inter(t_Intersection *inter, float dist, unsigned int color,
		t_object *obj)
{
	inter->min_dist = dist;
	inter->min_color = color;
	inter->object = obj;
}

t_Vector3	reflect(t_Vector3 I, t_Vector3 N)
{
	float	dot_product;

	dot_product = vector_dot(I, N);
	return (vector_sub(I, vector_scale(N, 2.0f * dot_product)));
}

int	check_light(t_scene *scene, t_Vector3 cam_origin, t_Vector3 ray_dir,
		float min_dist)
{
	t_Vector3	intersection_point;
	t_Vector3	light_dir;
	float		light_distance;
	t_object	*obj;
	float		shadow_dist;

	intersection_point = vector_add(cam_origin, vector_scale(ray_dir,
				min_dist));
	light_dir = vector_sub(*scene->light->pos, intersection_point);
	light_distance = vector_magnitude(light_dir);
	light_dir = vector_normalize(light_dir);
	obj = scene->objects;
	while (obj)
	{
		shadow_dist = FLT_MAX;
		get_intersection(obj, intersection_point, light_dir, &shadow_dist);
		if (shadow_dist > 0.001f && shadow_dist < light_distance)
			return (0);
		obj = obj->next;
	}
	return (1);
}

int	check_coll(t_Vector3 ray_dir, t_scene *escena, t_object *obj)
{
	t_Intersection	in;
	float			temp_dist;
	unsigned int	tc;
	int				light;

	in.min_dist = FLT_MAX;
	in.min_color = 0;
	in.object = NULL;
	light = 0;
	while (obj)
	{
		temp_dist = FLT_MAX;
		tc = get_intersection(obj, *escena->cam->pos, ray_dir, &temp_dist);
		if (temp_dist < in.min_dist)
			set_inter(&in, temp_dist, tc, obj);
		obj = obj->next;
	}
	light = check_light(escena, *escena->cam->pos, ray_dir, in.min_dist);
	if (!light)
		in.min_color = color_merge(in.min_color, *escena->seting->ambient_col);
	if (in.object && light && !is_inside(escena, in.object))
		in.min_color = shade(in, ray_dir, escena, light);
	else
		in.min_color = rgb_to_rgba(*escena->seting->ambient_col);
	return (in.min_color);
}
