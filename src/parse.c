/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:10:06 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/26 10:08:34 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"
# include <unistd.h>
# include "get_next_line.h"
# include "libft.h"

float   ft_atof(char *n)
{
    int     i;
    int     j;
    float   nb;
    int     m;
    i = 0;
    nb = 0;
    m = 1;
    j = 1;
    if (n[i] == '-')
    {
        m = -m;
        i++;
    }
    while (n[i] && n[i] != '\n')
    {
        if (j > 1 && n[i - 1] != '.')
            j *= 10;
        if (n[i] == '.')
            j *= 10;
        else
            nb = nb * 10 + (n[i] - 48);
        i++;
    }
    return (m * nb / j);
}

int array_len(char **array)
{
    int c;

    c = 0;
    while (array[c])
        c++;
    return (c);
}

void set_color(t_RGB *color,char **col_num)
{
    color->r = (ft_atoi (col_num[0]));
    color->g = (ft_atoi (col_num[1]));
    color->b = (ft_atoi (col_num[2]));
}

int is_float_array(char  *str)
{
   int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            if (str[i]!= '.' && str[i]!= '-')
                return (1);
        i++;
    }
    return (0);
}

int valid_iii(char **str)
{
    int tmp;
    int c;
    
    tmp = 0;
    c = 0;
    if( array_len(str) != 3 )
        return(1);
    while (c < 3)
    {
        tmp = ft_atoi(str[c++]);
        if (tmp < 0 || tmp > 255)
            return (1);
    }
    return (0);
}

int valid_fff(char **str)
{
    int     c;
    
    c = 0;
    if( array_len(str) != 3 )
        return(1);
    while (c < 3)
    {
        if (is_float_array (str[c]))
            return(1);
        c++;  
    }
    return (0);
}


int setambient(t_scene *scene, char  **line_split, int *error)
{
    int     i;
    char    **color;
    float   intensity;
    
    reserve_ambient(scene, error);
    i = 1;
    if (is_float_array(line_split[i]))
        return (*error = 1, 1);
    intensity = ft_atof(line_split[i++]);
    color = ft_split(line_split[i], ',');
    if (valid_iii(color))
        return (*error = 1, 1);    
    set_color(scene->seting->ambient_col, color);
    return (0);
}
void set_pos(t_Vector3 *pos, char **pos_a)
{
    pos->x = ft_atof(pos_a[0]);
    pos->y = ft_atof(pos_a[1]);
    pos->z = ft_atof(pos_a[2]);
}

void set_rot(t_Vector3 *pos, char **pos_a)
{
    pos->x = ft_atof(pos_a[0]);
    pos->y = ft_atof(pos_a[1]);
    pos->z = ft_atof(pos_a[2]);
}

int setcamera(t_scene *scene,char **line_split, int *error)
{
    char    **tmp;
    int     i;
       
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

int setlight(t_scene *scene,char **line_split, int *error)
{
    char    **tmp;
    int     i;
    t_light *last_light;
    t_light *light;
     
    i = 1;
    light = reserve_light(error);
    tmp = ft_split(line_split[i++], ',');
    if (valid_fff(tmp))
        return (*error = 1, 1);
    set_pos(light->pos, tmp);
    if (is_float_array( line_split[i]))
        return (*error = 1, 1);
    light->intensity = ft_atof(line_split[i++]);
    tmp = ft_split(line_split[i++], ',');
    if (valid_iii(tmp))
        return (*error = 1, 1);
    set_color(light->color,tmp );
    if (!scene->light)
    { 
        scene->light = light;
        return (0);
        
    }
    last_light = scene->light;
    while (last_light->next)
        last_light = last_light->next;
    last_light->next = light;
    return (0);
}

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
    set_rot(props->rot, tmp);
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
