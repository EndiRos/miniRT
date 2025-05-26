/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:38:12 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/26 11:39:24 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	tovec(t_Vector3 *vector, double x, double y ,double z)
{
    vector->x = x;
    vector->y = y;
    vector->z = z;
}

void	tocolor(t_RGB *vector, float r, float g ,float b)
{
    vector->r = r;
    vector->g = g;
    vector->b = b;
}

t_Vector3	rotate_vector(t_Vector3 v, t_Vector3 rot)
{
	t_Vector3	sin;
	t_Vector3	cos;
	t_Vector3	v1;
	t_Vector3	v2;
	t_Vector3	v3;

	tovec(&sin, sinf(rot.x), sinf(rot.y), sinf(rot.z));
	tovec(&cos, cosf(rot.x), cosf(rot.y), cosf(rot.z));
	tovec(&v1, v.x, v.y * cos.x - v.z * sin.x, v.y * sin.x + v.z * cos.x);
	tovec(&v2, v1.x * cos.y + v1.z * sin.y, v1.y, -v1.x * sin.y + v1.z * cos.y);
	tovec(&v3, v2.x * cos.z - v2.y * sin.z, v2.x * sin.z + v2.y * cos.z, v2.z);
	return (v3);
}