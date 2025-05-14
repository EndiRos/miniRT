/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:46 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/14 12:11:13 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

enum					e_obj_type
{
	SPHERE,
	CYLINDER,
	PLANE
};

typedef struct s_Vector3
{
	float				x;
	float				y;
	float				z;
}						t_Vector3;

typedef struct s_RGB
{
	float				r;
	float				g;
	float				b;
}						t_RGB;

typedef struct s_camera
{
	t_Vector3			pos;
	t_Vector3			rot;
	double				fov;
}						t_camera;

typedef struct s_light
{
	t_Vector3			pos;
	t_RGB				color;
	float				intensity;
}						t_light;

typedef struct s_cyl_prop
{
	t_Vector3			pos;
	t_Vector3			rot;
	float				radius;
	float				height;
	t_RGB				color;
}						t_cyl_prop;

typedef struct s_sphere_prop
{
	t_Vector3			pos;
	t_Vector3			rot;
	float				radius;
	t_RGB				color;
}						t_sphere_prop;

typedef struct s_plane_prop
{
	t_Vector3			pos;
	t_Vector3			normal;
	t_RGB				color;
}						t_plane_prop;

typedef struct s_objects
{
	enum e_obj_type		obj_type;
	void				*props;
	struct s_objects	*next;
}						t_object;

typedef struct s_settings
{
	t_RGB				ambient_col;
	float				intensity;
}						t_settings;

typedef struct s_scene
{
	t_camera			*cam;
	t_light				*light;
	t_object			*objects;
	t_settings			*seting;
}						t_scene;

typedef struct s_material
{
	float				difuse;
	float				specular;
	float				reflexion;
	float				refraction;
	float				IOR;
}						t_material;

t_Vector3				vector_add(t_Vector3 a, t_Vector3 b);

t_Vector3				vector_sub(t_Vector3 a, t_Vector3 b);

float					vector_dot(t_Vector3 a, t_Vector3 b);

float					vector_magnitude(t_Vector3 v);

t_Vector3				vector_normalize(t_Vector3 v);

t_Vector3				vector_scale(t_Vector3 v, float scalar);

int						quadratic(float a, float b, float c, float *t0);
int						ray_sphere_intersect(t_Vector3 ray_orig,
							t_Vector3 ray_dir, t_sphere_prop sphere, float *t0);
int						ray_plane_intersect(t_Vector3 ray_orig,
							t_Vector3 ray_dir, t_plane_prop plane, float *t);
int						ray_cylinder_intersect(t_Vector3 ray_orig,
							t_Vector3 ray_dir, t_cyl_prop cyl, float *t_out);