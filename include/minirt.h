/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:46 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/22 11:01:29 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "get_next_line.h"
#include "libft.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum e_obj_type
{
	SPHERE,
	CYLINDER,
	PLANE
}					t_obj_type;

typedef struct s_Vector3
{
	float			x;
	float			y;
	float			z;
}					t_Vector3;

typedef struct s_RGB
{
	int				r;
	int				g;
	int				b;
}					t_RGB;

typedef struct s_camera
{
	t_Vector3		pos;
	t_Vector3		rot;
	float fov; //( M_PI / 180f )* FOV
	float			aspect_ratio;
	float scale; // tanf(fov/2.0f)
}					t_camera;

typedef struct s_light
{
	t_Vector3		pos;
	t_RGB			color;
	float			intensity;
}					t_light;

typedef struct s_material
{
	t_RGB			difuse;
	t_RGB			specular;
	t_RGB			reflexion;
	t_RGB			refraction;
	float			IOR;
}					t_material;

typedef struct s_cyl_prop
{
	t_Vector3		pos;
	t_Vector3		rot;
	float			radius;
	float			height;
	t_material		*material;
}					t_cyl_prop;

typedef struct s_sphere_prop
{
	t_Vector3		pos;
	t_Vector3		rot;
	float			radius;
	t_material		*material;
}					t_sphere_prop;

typedef struct s_plane_prop
{
	t_Vector3		pos;
	t_Vector3		normal;
	t_material		*material;
}					t_plane_prop;

typedef struct s_object
{
	enum e_obj_type	obj_type;
	void			*props;
	struct s_object	*next;
}					t_object;

typedef struct s_settings
{
	t_RGB			ambient_col;
	float			intensity;
}					t_settings;

typedef struct s_scene
{
	t_camera		*cam;
	t_light			*light;
	t_object		*objects;
	t_settings		*seting;
}					t_scene;

typedef struct s_Intersection
{
	float			min_dist;
	unsigned int	min_color;
	t_object		*object;
}					t_Intersection;

typedef struct s_shade
{
	t_Vector3		hit_point;
	t_Vector3		normal;
	t_Vector3		light_dir;
	t_Vector3		view_dir;
	t_Vector3		reflected;
}					t_shade;

t_Vector3			vector_add(t_Vector3 a, t_Vector3 b);

t_Vector3			vector_sub(t_Vector3 a, t_Vector3 b);

float				vector_dot(t_Vector3 a, t_Vector3 b);

float				vector_magnitude(t_Vector3 v);

t_Vector3			vector_normalize(t_Vector3 v);

t_Vector3			vector_scale(t_Vector3 v, float scalar);

int					quadratic(float a, float b, float c, float *t0);
unsigned int		ray_sphere_intersect(t_Vector3 ray_orig, t_Vector3 ray_dir,
						t_sphere_prop sphere, float *t0);
unsigned int		ray_plane_intersect(t_Vector3 ray_orig, t_Vector3 ray_dir,
						t_plane_prop plane, float *t);
unsigned int		ray_cylinder_intersect(t_Vector3 ray_orig,
						t_Vector3 ray_dir, t_cyl_prop cyl, float *t_out);

unsigned int		rgb_to_rgba(t_RGB rgb);
t_RGB				rgba_to_rgb(unsigned int color);

t_Vector3			sphere_normal(t_sphere_prop *sphere, t_Vector3 point);
t_Vector3			plane_normal(t_plane_prop *plane);
t_Vector3			cylinder_normal(t_cyl_prop *cyl, t_Vector3 point);

t_scene				*harcoding(void);
void				tocolor(t_RGB *vector, float r, float g, float b);
void				tovec(t_Vector3 *vector, double x, double y, double z);
void				calculate_image(mlx_image_t *image, t_scene *escena);

void				tovec(t_Vector3 *vector, double x, double y, double z);
