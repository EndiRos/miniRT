/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:20:16 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/26 11:20:19 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_obj(t_scene *scene)
{
	t_object	*tmp_obj;

	if (!scene->objects)
		return ;
	while (scene->objects)
	{
		tmp_obj = scene->objects->next;
		if (scene->objects->obj_type == SPHERE)
			free_sphere(scene->objects->props);
		else if (scene->objects->obj_type == PLANE)
			free_plane(scene->objects->props);
		else if (scene->objects->obj_type == CYLINDER)
			free_cylinder(scene->objects->props);
		free(scene->objects);
		scene->objects = tmp_obj;
	}
}

void	free_light(t_scene *scene)
{
	t_light	*tmp;

	if (scene->light == NULL)
		return ;
	while (scene->light)
	{
		free(scene->light->color);
		free(scene->light->pos);
		tmp = scene->light;
		scene->light = scene->light->next;
		free(tmp);
	}
	return ;
}

void	free_cam(t_scene *scene)
{
	if (scene->cam == NULL)
		return ;
	free(scene->cam->pos);
	free(scene->cam->rot);
	free(scene->cam);
	return ;
}

void	free_escena(t_scene **scene)
{
	free_stting(*scene);
	free_cam(*scene);
	free_light(*scene);
	free_obj(*scene);
	free(*scene);
}
