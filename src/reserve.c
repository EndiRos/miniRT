/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:31:34 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/26 12:00:26 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material *reserve_material(int *error)
{
    t_material *mat;
	
	mat = (t_material *)malloc(sizeof(t_material));
	if (!mat)
		return (*error = 2, NULL);
	ft_memset(mat, 0, sizeof(t_material)); 
    mat->difuse = reserve_rgb(error);
    mat->specular = reserve_rgb(error);
	mat->reflexion =  reserve_rgb(error);
	mat->refraction = reserve_rgb(error);
    return mat;
}

void reserve_ambient(t_scene *scene, int *error)
{
	scene->seting =  malloc (sizeof(t_settings));
	if (!scene->seting)
	{	
		*error = 2;
		return ;
	}
	ft_memset(scene->seting, 0, sizeof(t_settings));
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
	ft_memset(scene->cam, 0, sizeof(t_camera)); 
	scene->cam->pos =reserve_vector(error);
	scene->cam->rot = reserve_vector(error);
}

t_light *reserve_light(int *error)
{
	t_light *light;
	
	light = (t_light *) malloc (sizeof (t_light));
	if (!light)
		return (*error = 2, NULL);
	ft_memset(light, 0, sizeof(t_light)); 
	light->color =  reserve_rgb(error);
	light->pos =  reserve_vector(error);
	light->next = NULL;
	light->intensity = 0.0;
	return (light);
}
