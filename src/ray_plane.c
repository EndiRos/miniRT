/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:17:32 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/27 12:17:33 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	ray_plane_intersect(t_Vector3 ray_orig, t_Vector3 ray_dir,
		t_plane_prop plane, float *t)
{
	t_Vector3	n;
	float		t_val;
	float		denominator;
	int			res;

	res = 1;
	n = vector_normalize(*plane.rot);
	denominator = vector_dot(ray_dir, n);
	if (fabsf(denominator) < 1e-6)
		return (0);
	t_val = vector_dot(vector_sub(*plane.pos, ray_orig), n) / denominator;
	if (t_val < 0.0001f)
		res = 0;
	if (res)
	{
		if (t_val < *t)
			*t = t_val;
		return (rgb_to_rgba(*plane.material->difuse));
	}
	return (255);
}
