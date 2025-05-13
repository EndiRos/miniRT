/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:46 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/13 11:06:56 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

typedef struct s_Vector3
{
	float	x;
	float	y;
	float	z;
}			t_Vector3;

typedef struct s_RGB
{
	float	r;
	float	g;
	float	b;
}			t_RGB;

typedef struct s_camera
{
	t_Vector3	pos;
	t_Vector3	rot;
	double		fov;
}			t_camera;

typedef struct s_light
{
	t_Vector3	pos;
	t_RGB		color;
	float		intensity;
}			t_light;

typedef struct s_cyl_prop
{
	t_Vector3		pos;
	t_Vector3		rot;
	float			radius;
	float			height;
	t_RGB			color;
}			t_cyl_prop;

typedef struct s_sphere_prop
{
	t_Vector3		pos;
	t_Vector3		rot;
	float			radius;
	t_RGB			color;
}			t_sphere_prop;

typedef struct s_plane_prop
{
	t_Vector3		pos;
	t_Vector3		normal;
	t_RGB			color;
}			t_plane_prop;

typedef struct s_objects
{
	enum e_obj_type	obj_type;
	void			*props;
	t_object		*next;
}			t_object;


typedef struct s_settings
{

	t_RGB		ambient_col;
	float		intensity;
}			t_settings;

typedef struct s_scene
{
	t_camera	*cam;
	t_light		*light;
	t_object	*objects;
	t_settings	*seting;
}				t_scene;


enum		e_obj_type
{
	SPHERE,
	CYLINDER,
	PLANE
};

typedef struct s_material
{
	float	difuse;
	float	specular;
	float	reflexion;
	float	refraction;
	float	IOR;
}				t_scene;
