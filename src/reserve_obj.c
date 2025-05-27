/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserve_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:34 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/27 14:34:09 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*reserve_obj(int *error)
{
	t_object	*obj;

	obj = (t_object *) malloc (sizeof (t_object));
	if (!obj)
		return (*error = 2, NULL);
	ft_memset(obj, 0, sizeof(t_obj_type));
	obj->next = NULL;
	return (obj);
}

t_plane_prop	*reserve_plane(int *error)
{
	t_plane_prop	*plane;

	plane = (t_plane_prop *) malloc (sizeof (t_plane_prop));
	if (!plane)
	{	
		*error = 2;
		return (NULL);
	}
	ft_memset(plane, 0, sizeof(t_plane_prop));
	plane->pos = reserve_vector(error);
	plane->rot = reserve_vector(error);
	plane->material = reserve_material(error);
	return (plane);
}

t_sphere_prop	*reserve_sphere(int *error)
{
	t_sphere_prop	*obj;

	obj = (t_sphere_prop *) malloc (sizeof (t_sphere_prop));
	if (!obj)
	{	
		*error = 2;
		return (NULL);
	}
	ft_memset(obj, 0, sizeof(t_sphere_prop));
	obj->pos = reserve_vector(error);
	obj->rot = reserve_vector(error);
	obj->material = reserve_material(error);
	obj->radius = 0.0;
	return (obj);
}

t_cyl_prop	*reserve_cyl(int *error)
{
	t_cyl_prop	*obj;

	obj = (t_cyl_prop *) malloc (sizeof (t_cyl_prop));
	if (!obj)
	{	
		*error = 2;
		return (NULL);
	}
	ft_memset(obj, 0, sizeof(t_cyl_prop));
	obj->pos = reserve_vector(error);
	obj->rot = reserve_vector(error);
	obj->material = reserve_material(error);
	return (obj);
}
