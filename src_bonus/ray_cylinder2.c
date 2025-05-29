/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:09:37 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/28 13:59:23 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vector3	cyl_get_cap_center(t_cyl_prop cyl, int is_top)
{
	float	half_height;
	float	sign;

	half_height = 0.5f * cyl.height;
	if (is_top)
		sign = 1.0f;
	else
		sign = -1.0f;
	return (vector_add(*cyl.pos, vector_scale(*cyl.rot, sign * half_height)));
}

int	cyl_check_cap_hit(t_Vector3 ray_orig, t_Vector3 ray_dir, t_CylCapData cyl,
		float *best_t)
{
	t_Vector3	oc_to_cap;
	float		denom;
	float		t;
	t_Vector3	p_cap;
	t_Vector3	pc_cap;

	oc_to_cap = vector_sub(cyl.cap, ray_orig);
	denom = vector_dot(ray_dir, *cyl.cyl.rot);
	if (fabsf(denom) < 0.000001f)
		return (0);
	t = vector_dot(oc_to_cap, *cyl.cyl.rot) / denom;
	if (t < 0.001f || t >= *best_t)
		return (0);
	p_cap = vector_add(ray_orig, vector_scale(ray_dir, t));
	pc_cap = vector_sub(p_cap, cyl.cap);
	if (vector_dot(pc_cap, pc_cap) <= cyl.cyl.radius * cyl.cyl.radius
		+ 0.00001f)
	{
		*best_t = t;
		return (1);
	}
	return (0);
}

int	cyl_top_bot_coll(t_Vector3 ray_orig, t_Vector3 ray_dir, t_cyl_prop cyl,
		float *t_out)
{
	int				hit;
	float			best_t;
	t_CylCapData	data;

	data.cyl = cyl;
	hit = 0;
	best_t = *t_out;
	data.cap = cyl_get_cap_center(cyl, 0);
	if (cyl_check_cap_hit(ray_orig, ray_dir, data, &best_t))
		hit = 1;
	data.cap = cyl_get_cap_center(cyl, 1);
	if (cyl_check_cap_hit(ray_orig, ray_dir, data, &best_t))
		hit = 1;
	if (hit)
		*t_out = best_t;
	return (hit);
}
