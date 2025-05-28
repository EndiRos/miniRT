/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:17:55 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/28 11:35:13 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	quadratic(float a, float b, float c, float *t0)
{
	float	discriminant;
	float	sqrt_disc;
	float	t1;
	float	t2;

	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
		return (0);
	sqrt_disc = sqrtf(discriminant);
	t1 = (-b - sqrt_disc) / (2 * a);
	t2 = (-b + sqrt_disc) / (2 * a);
	if (t1 > 0.001f && (t1 < t2 || t2 < 0.001f))
	{
		*t0 = t1;
		return (1);
	}
	else if (t2 > 0.001f)
	{
		*t0 = t2;
		return (1);
	}
	return (0);
}

unsigned int	ray_sphere_intersect(t_Vector3 ray_orig, t_Vector3 ray_dir,
		t_sphere_prop sphere, float *t0)
{
	t_Vector3	l;
	float		t1;
	int			res;

	res = 0;
	t1 = *t0;
	l = vector_sub(ray_orig, *sphere.pos);
	res = quadratic(vector_dot(ray_dir, ray_dir), 2.0f * vector_dot(ray_dir, l),
			vector_dot(l, l) - sphere.radius * sphere.radius, &t1);
	if (res)
	{
		if (t1 < *t0)
			*t0 = t1;
		return (rgb_to_rgba(*sphere.material->difuse));
	}
	return (255);
}
