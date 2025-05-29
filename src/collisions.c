/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:40:45 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/29 11:48:12 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	point_in_cyl(t_cyl_prop cyl, t_Vector3 cam_pos)
{
	t_Vector3	w;
	float		t;
	float		half_height;
	t_Vector3	w_perp;
	float		dist;

	w = vector_sub(cam_pos, *cyl.pos);
	t = vector_dot(w, *cyl.rot);
	half_height = cyl.height * 0.5f;
	if (t < -half_height || t > half_height)
		return (0);
	w_perp = vector_sub(w, vector_scale(*cyl.rot, t));
	dist = vector_magnitude(w_perp);
	if (dist > cyl.radius)
		return (0);
	return (1);
}

int	is_inside(t_scene *escena, t_object *obj)
{
	float			dist;
	t_sphere_prop	sphere;
	t_cyl_prop		cyl;

	if (!obj)
		return (1);
	if (obj->obj_type == SPHERE)
	{
		sphere = *(t_sphere_prop *)obj->props;
		dist = vector_magnitude(vector_sub(*escena->cam->pos, *sphere.pos));
		if (dist > sphere.radius)
			return (0);
		return (1);
	}
	else if (obj->obj_type == CYLINDER)
	{
		cyl = *(t_cyl_prop *)obj->props;
		return (point_in_cyl(cyl, *escena->cam->pos));
	}
	return (0);
}
