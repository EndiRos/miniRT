/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:34 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/22 10:12:22 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_RGB *reserve_rgb(int *error)
{
    t_RGB *color = (t_RGB *)malloc(sizeof(t_RGB));
	if (!color)
		return (*error = 2, NULL); 
    return color;
}
t_material *reserve_material(int *error)
{
    t_material *mat;
	
	mat = (t_material *)malloc(sizeof(t_material));
	if (!mat)
		return (*error = 2, NULL); 
    mat->difuse = reserve_rgb(error);
    mat->specular = reserve_rgb(error);
	mat->reflexion =  reserve_rgb(error);
	mat->refraction = reserve_rgb(error);
    return mat;
}
t_Vector3	*reserve_vector(int *error)
{
	t_Vector3 *vec;
	
	vec = (t_Vector3 *) malloc (sizeof (t_Vector3));
	if (!vec)
		return (*error = 2, NULL); 
	return (vec);	
}


void reserve_ambient(t_scene *scene, int *error)
{
	scene->seting =  malloc (sizeof(t_settings));
	if (!scene->seting)
	{	
		*error = 2;
		return ;
	} 
	scene->seting->ambient_col = (t_RGB *)malloc (sizeof(t_RGB));
	if (!scene->seting->ambient_col)
	{	
		*error = 2;
		return ;
	} 
}

void reserve_cam(t_scene *scene, int *error)
{
	scene->cam = (t_camera *) malloc (sizeof (t_camera));
	if (!scene->cam)
	{	
		*error = 2;
		return ;
	} 
	scene->cam->pos =reserve_vector(error);
	scene->cam->rot = reserve_vector(error);
}

t_light *reserve_light(int *error)
{
	t_light *light;
	
	light = (t_light *) malloc (sizeof (t_light));
	if (!light)
		return (*error = 2, NULL); 
	light->color =  reserve_rgb(error);
	light->pos =  reserve_vector(error);
	light->next = NULL;
	return (light);
}

t_object	*reserve_obj(int *error)
{
	t_object *obj;
	
	obj = (t_object *) malloc (sizeof (t_object));
	if (!obj)
		return (*error = 2, NULL);
	obj->next = NULL;
	return (obj);
}

t_plane_prop *reserve_plane(int *error)
{
	t_plane_prop *plane;

	plane = (t_plane_prop *) malloc (sizeof (t_plane_prop));
	if (!plane)
	{	
		*error = 2;
		return (NULL);
	} 
	plane->pos = reserve_vector(error);
	plane->rot = reserve_vector(error);
	plane->material = reserve_material(error);
	return(plane);

}
t_sphere_prop *reserve_sphere(int *error)
{
	t_sphere_prop *obj;

	obj = (t_sphere_prop *) malloc (sizeof (t_sphere_prop));
	if (!obj)
	{	
		*error = 2;
		return (NULL) ;
	} 
	obj->pos = reserve_vector(error);
	obj->rot = reserve_vector(error);
	obj->material = reserve_material(error);
	return (obj);

}

t_cyl_prop *reserve_cyl (int *error)
{
	t_cyl_prop *obj;

	obj = (t_cyl_prop *) malloc (sizeof (t_cyl_prop));
	if (!obj)
	{	
		*error = 2;
		return (NULL);
	} 
	obj->pos = reserve_vector(error);
	obj->rot = reserve_vector(error);
	obj->material = reserve_material(error);
	return (obj);
}