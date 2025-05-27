/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:10:06 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/27 11:14:49 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"
# include <unistd.h>
# include "get_next_line.h"
# include "libft.h"

int setplane(t_scene **scene, char **line_split, int *error)
{
    char    **tmp;
    int     i;
    t_object *last_obj;
    t_object *obj;
    t_plane_prop *props;
     
    i = 1;
    obj = reserve_obj(error);
    obj->obj_type = PLANE;
    props = reserve_plane(error);
    tmp = ft_split(line_split[i++], ',');
    if (valid_fff(tmp))
        return (*error = 1, 1);
    set_pos(props->pos, tmp);
    tmp = ft_split(line_split[i++], ',');
    if (valid_fff(tmp))
        return (*error = 1, 1);
    set_rot(props->rot , tmp);
    tmp = ft_split(line_split[i++], ',');
    if (valid_iii(tmp))
        return (*error = 1, 1);
    set_color(props->material->difuse, tmp );
    obj->next = NULL;
    obj->props = props;
    
    if (!(*scene)->objects)
    { 
        (*scene)->objects = obj;
        return (0); 
    }
    last_obj = (*scene)->objects;
    while (last_obj->next)
        last_obj = last_obj->next;
    last_obj->next = obj;
    return (0);
}

int setsphere(t_scene **scene, char **line_split, int *error)
{
    char            **tmp;
    int             i;
    t_object        *last_obj;
    t_object        *obj;
    t_sphere_prop   *props;
     
    i = 1;
    obj = reserve_obj(error);
    obj->obj_type = SPHERE;
    props = reserve_sphere(error);
    tmp = ft_split(line_split[i++], ',');
    if (valid_fff(tmp))
        return (*error = 1, 1);
    set_pos(props->pos, tmp);
    if (is_float_array(line_split[i]))
        return (*error = 1, 1);
    props->radius = ft_atof(line_split[i++]);
    tmp = ft_split(line_split[i++], ',');
    if (valid_iii(tmp))
        return (*error = 1, 1);
    set_color(props->material->difuse, tmp );
    obj->props = props;
    obj->next = NULL;
    if (!(*scene)->objects)
    { 
        (*scene)->objects = obj;
        return (0); 
    }
    last_obj = (*scene)->objects;
    while (last_obj->next)
        last_obj = last_obj->next;
    last_obj->next = obj;
    return (0);
}

int setcylinder(t_scene **scene, char **line_split, int *error)
{
    char            **tmp;
    int             i;
    t_object        *last_obj;
    t_object        *obj;
    t_cyl_prop      *props;
     
    i = 1;
    obj = reserve_obj(error);
    obj->obj_type = CYLINDER;
    props = reserve_cyl(error);
    tmp = ft_split(line_split[i++], ',');
    if (valid_fff(tmp))
        return (*error = 1, 1);
    set_pos(props->pos, tmp);
    tmp = ft_split(line_split[i++], ',');
    if (valid_fff(tmp))
        return (*error = 1, 1);
    set_rot((props->rot), tmp);
    if (is_float_array(line_split[i]))
        return (*error = 1, 1);
    props->radius = ft_atof(line_split[i++]);
    if (is_float_array(line_split[i]))
        return (*error = 1, 1);
    props->height = ft_atof(line_split[i++]);
    tmp = ft_split(line_split[i++], ',');
    if (valid_iii(tmp))
        return (*error = 1, 1);
    set_color(props->material->difuse, tmp );
    obj->props = props;
    obj->next = NULL;
    if (!(*scene)->objects)
    { 
        (*scene)->objects = obj;
        return (0); 
    }
    last_obj = (*scene)->objects;
    while (last_obj->next)
        last_obj = last_obj->next;
    last_obj->next = obj;
    return (0);
}

void parse(t_scene *scene, char *file)
{
    char    *line;
    int     fd;
    char    **line_split;
    int     error;
    
	error = 0;
    fd = open (file,0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_split = ft_split(line, ' ');
        if (!ft_strncmp (line_split[0],"A",1))
            setambient(scene, line_split, &error);
        else  if (!ft_strncmp (line_split[0],"C",1))
            setcamera(scene, line_split, &error);
        else  if (!(ft_strncmp (line_split[0],"L", 1)))
            setlight(scene, line_split, &error);
        else  if (!(ft_strncmp (line_split[0],"pl",2)))
            setplane(&scene, line_split, &error);
        else  if (!(ft_strncmp (line_split[0],"sp",2)))
            setsphere(&scene, line_split, &error);
        else  if (!(ft_strncmp (line_split[0],"cy",2)))
            setcylinder(&scene, line_split, &error);
        else
           error= 1;
        free(line);
		if (error == 1)
        {
            //destroy_all();
            perror("Error: bad format file");
            close (fd);
            exit (1);
        }
        else if (error == 1)
        {   
            perror("Error: Malloc error");
            close (fd);
            exit (1);
        }
		line = get_next_line(fd);
	}
}
/*
int main (int argc, char **argv)
{
    t_scene *escena;
    int stop;
    
    escena = (t_scene *) malloc (sizeof (t_scene));
    parse(escena, argv[1]);
    free_escena(&escena);
    stop = 0;
}
*/
