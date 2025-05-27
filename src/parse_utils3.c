/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:57:51 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/27 14:28:18 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	**split_fff(char *line_split, int *error, int *i)
{
	char	**tmp;

	if (!line_split[*i])
		return (*error = 1, NULL);
	tmp = ft_split(line_split, ',');
	if (!tmp)
		return (*error = 2, NULL);
	(*i)++;
	if (valid_fff(tmp))
		return (*error = 1, NULL);
	return (tmp);
}

char	**split_iii(char *line_split, int *error, int *i)
{
	char	**tmp;

	if (!line_split[*i])
		return (*error = 1, NULL);
	tmp = ft_split(line_split, ',');
	if (!tmp)
		return (*error = 2, NULL);
	(*i)++;
	if (valid_iii(tmp))
		return (*error = 1, NULL);
	return (tmp);
}

void	add_to_end(t_scene **scene, t_object *obj)
{
	t_object	*last_obj;

	if (!(*scene)->objects)
	{
		(*scene)->objects = obj;
		return ;
	}
	last_obj = (*scene)->objects;
	while (last_obj->next)
		last_obj = last_obj->next;
	last_obj->next = obj;
	return ;
}

void	set_options(t_scene *scene, char **line_split, int *error)
{
	if (!ft_strncmp(line_split[0], "A", 1))
		setambient(scene, line_split, error);
	else if (!ft_strncmp(line_split[0], "C", 1))
		setcamera(scene, line_split, error);
	else if (!(ft_strncmp(line_split[0], "L", 1)))
		setlight(scene, line_split, error);
	else if (!(ft_strncmp(line_split[0], "pl", 2)))
		setplane(&scene, line_split, error);
	else if (!(ft_strncmp(line_split[0], "sp", 2)))
		setsphere(&scene, line_split, error);
	else if (!(ft_strncmp(line_split[0], "cy", 2)))
		setcylinder(&scene, line_split, error);
	else
		*error = 1;
}

void	on_error(t_scene **scene, int *error, int fd)
{
	if (*error == 1)
	{
		free_escena(scene);
		perror("Error: bad format file");
		close(fd);
		exit(1);
	}
	else if (*error == 2)
	{
		perror("Error: Malloc error");
		close(fd);
		exit(1);
	}
}
