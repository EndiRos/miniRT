/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:25:46 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/27 12:25:49 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_Vector3	vector_scale(t_Vector3 v, float scalar)
{
	return ((t_Vector3){v.x * scalar, v.y * scalar, v.z * scalar});
}

t_Vector3	vector_cross(t_Vector3 a, t_Vector3 b)
{
	return ((t_Vector3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
		- a.y * b.x});
}
