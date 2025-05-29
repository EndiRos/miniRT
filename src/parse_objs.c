/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:10:06 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/29 11:11:27 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	setplane(t_scene **scene, char **line_split, int *error)
{
	int				i;
	t_object		*obj;
	t_plane_prop	*props;

	i = 1;
	obj = reserve_obj(error);
	obj->obj_type = PLANE;
	props = reserve_plane(error);
	set_pos(props->pos, split_fff(line_split[i], error, &i));
	set_rot(props->rot, split_fff(line_split[i], error, &i));
	set_color(props->material->difuse, split_iii(line_split[i++], error, &i));
	obj->next = NULL;
	obj->props = props;
	add_to_end(scene, obj);
	return (0);
}

int	setsphere(t_scene **scene, char **line_split, int *error)
{
	int				i;
	t_object		*obj;
	t_sphere_prop	*props;

	i = 1;
	obj = reserve_obj(error);
	obj->obj_type = SPHERE;
	props = reserve_sphere(error);
	set_pos(props->pos, split_fff(line_split[i], error, &i));
	if (is_float_array(line_split[i]))
		return (*error = 1, 1);
	props->radius = ft_atof(line_split[i++]) / 2;
	set_color(props->material->difuse, split_iii(line_split[i++], error, &i));
	obj->props = props;
	obj->next = NULL;
	add_to_end(scene, obj);
	return (0);
}

int	setcylinder(t_scene **scene, char **line_split, int *error)
{
	int			i;
	t_object	*obj;
	t_cyl_prop	*props;

	i = 1;
	obj = reserve_obj(error);
	obj->obj_type = CYLINDER;
	props = reserve_cyl(error);
	set_pos(props->pos, split_fff(line_split[i], error, &i));
	set_rot(props->rot, split_fff(line_split[i], error, &i));
	if (is_float_array(line_split[i]))
		return (*error = 1, 1);
	props->radius = ft_atof(line_split[i++]) / 2;
	if (is_float_array(line_split[i]))
		return (*error = 1, 1);
	props->height = ft_atof(line_split[i++]);
	set_color(props->material->difuse, split_iii(line_split[i++], error, &i));
	obj->props = props;
	obj->next = NULL;
	add_to_end(scene, obj);
	return (0);
}

void	parse(t_scene *scene, char *file)
{
	char	*line;
	int		fd;
	char	**line_split;
	int		error;

	error = 0;
	fd = open(file, 0);
	if (fd == -1)
	{
		error = 4;
		on_error(&scene, &error);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_split = ft_split(line, ' ');
		set_options(scene, line_split, &error);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!scene->cam || !scene->light || !scene->seting)
		error = 3;
	on_error(&scene, &error);
}
