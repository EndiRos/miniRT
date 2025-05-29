/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:39:45 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/26 11:18:51 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_stting(t_scene *scene)
{
	if (!scene->seting)
		return ;
	free(scene->seting->ambient_col);
	free(scene->seting);
}

void	free_material(t_material *mat)
{
	if (!mat)
		return ;
	free(mat->difuse);
	free(mat->specular);
	free(mat->reflexion);
	free(mat->refraction);
}

void	free_sphere(t_sphere_prop *props)
{
	if (!props)
		return ;
	free(props->pos);
	free_material(props->material);
	free(props);
}

void	free_plane(t_plane_prop *props)
{
	if (!props)
		return ;
	free(props->pos);
	free(props->rot);
	free_material(props->material);
	free(props);
}

void	free_cylinder(t_cyl_prop *props)
{
	if (!props)
		return ;
	free(props->pos);
	free(props->rot);
	free_material(props->material);
	free(props);
}
