/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserve_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:34 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/27 14:36:06 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_RGB	*reserve_rgb(int *error)
{
	t_RGB	*color;

	color = (t_RGB *)malloc(sizeof(t_RGB));
	if (!color)
		return (*error = 2, NULL);
	ft_memset(color, 0, sizeof(t_RGB));
	color->r = 0.0;
	color->g = 0.0;
	color->b = 0.0;
	return (color);
}

t_Vector3	*reserve_vector(int *error)
{
	t_Vector3	*vec;

	vec = (t_Vector3 *) malloc (sizeof (t_Vector3));
	if (!vec)
		return (*error = 2, NULL);
	ft_memset(vec, 0, sizeof(t_Vector3));
	vec->x = 0.0;
	vec->y = 0.0;
	vec->z = 0.0;
	return (vec);
}
