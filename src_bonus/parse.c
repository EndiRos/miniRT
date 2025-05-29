/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:10:06 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/28 12:07:05 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	setambient(t_scene *scene, char **line_split, int *error)
{
	int		i;
	char	**color;
	float	intensity;

	reserve_ambient(scene, error);
	i = 1;
	if (is_float_array(line_split[i]))
		return (*error = 1, 1);
	intensity = ft_atof(line_split[i++]);
	color = ft_split(line_split[i], ',');
	if (valid_iii(color))
		return (*error = 1, 1);
	set_ambient_col(scene->seting->ambient_col, color, intensity);
	return (0);
}

int	setcamera(t_scene *scene, char **line_split, int *error)
{
	char	**tmp;
	int		i;

	i = 1;
	reserve_cam(scene, error);
	tmp = ft_split(line_split[i++], ',');
	if (valid_fff(tmp))
		return (*error = 1, 1);
	set_pos(scene->cam->pos, tmp);
	tmp = ft_split(line_split[i++], ',');
	if (valid_fff(tmp))
		return (*error = 1, 1);
	set_rot(scene->cam->rot, tmp);
	scene->cam->fov = (M_PI / 180.0f) * ft_atof(line_split[i++]);
	scene->cam->scale = tanf(scene->cam->fov / 2.0f);
	return (0);
}

void	add_light_scene(t_scene *scene, t_light *light)
{
	t_light	*last_light;

	if (!scene->light)
	{
		scene->light = light;
		return ;
	}
	last_light = scene->light;
	while (last_light->next)
		last_light = last_light->next;
	last_light->next = light;
}

int	setlight(t_scene *scene, char **line_split, int *error)
{
	char	**tmp;
	int		i;
	t_light	*light;

	i = 1;
	light = reserve_light(error);
	tmp = ft_split(line_split[i++], ',');
	if (valid_fff(tmp))
		return (*error = 1, 1);
	set_pos(light->pos, tmp);
	if (is_float_array(line_split[i]))
		return (*error = 1, 1);
	light->intensity = ft_atof(line_split[i++]);
	tmp = ft_split(line_split[i++], ',');
	if (valid_iii(tmp))
		return (*error = 1, 1);
	set_color(light->color, tmp);
	add_light_scene(scene, light);
	return (0);
}
