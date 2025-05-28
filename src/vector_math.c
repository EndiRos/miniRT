/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:19:45 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/27 12:25:34 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vector3	vector_add(t_Vector3 a, t_Vector3 b)
{
	return ((t_Vector3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_Vector3	vector_sub(t_Vector3 a, t_Vector3 b)
{
	return ((t_Vector3){a.x - b.x, a.y - b.y, a.z - b.z});
}

float	vector_dot(t_Vector3 a, t_Vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	vector_magnitude(t_Vector3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_Vector3	vector_normalize(t_Vector3 v)
{
	float	mag;

	mag = vector_magnitude(v);
	if (mag == 0.0f)
		return ((t_Vector3){0, 0, 0});
	return ((t_Vector3){v.x / mag, v.y / mag, v.z / mag});
}
