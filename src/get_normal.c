/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:22:14 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/27 11:42:37 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vector3	sphere_normal(t_sphere_prop *sphere, t_Vector3 point)
{
	return (vector_normalize(vector_sub(point, *sphere->pos)));
}

t_Vector3	plane_normal(t_plane_prop *plane)
{
	return (vector_normalize(*plane->rot));
}

t_Vector3	cylinder_normal(t_cyl_prop *cyl, t_Vector3 point)
{
	t_Vector3	ca;
	t_Vector3	cp;
	float		proj_len;
	t_Vector3	proj;

	ca = vector_normalize(*cyl->rot);
	cp = vector_sub(point, *cyl->pos);
	proj_len = vector_dot(cp, ca);
	if (proj_len >= cyl->height * 0.5f - 0.00005f)
		return (ca);
	if (proj_len <= -cyl->height * 0.5f + 0.00005f)
		return (vector_scale(ca, -1));
	proj = vector_scale(ca, proj_len);
	return (vector_normalize(vector_sub(cp, proj)));
}
