/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:46 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/28 12:07:46 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42/MLX42.h"
# include "get_next_line.h"
# include "libft.h"
# include <float.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
	float			r;
	float			g;
	float			b;
}					t_RGB;

typedef struct s_camera
{
	t_Vector3		*pos;
	t_Vector3		*rot;
	float fov; //( M_PI / 180f )* FOV
	float			aspect_ratio;
	float scale; // tanf(fov/2.0f)
}					t_camera;

typedef struct s_light
{
	t_Vector3		*pos;
	t_RGB			*color;
	float			intensity;
	struct s_light	*next;
}					t_light;

typedef struct s_material
{
	t_RGB			*difuse;
	t_RGB			*specular;
	t_RGB			*reflexion;
	t_RGB			*refraction;
	float			IOR;
}					t_material;

typedef struct s_cyl_prop
{
	t_Vector3		*pos;
	t_Vector3		*rot;
	float			radius;
	float			height;
	t_material		*material;
}					t_cyl_prop;

typedef struct s_sphere_prop
{
	t_Vector3		*pos;
	t_Vector3		*rot;
	float			radius;
	t_material		*material;
}					t_sphere_prop;

typedef struct s_plane_prop
{
	t_Vector3		*pos;
	t_Vector3		*rot;
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
	t_RGB			*ambient_col;
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

t_Vector3			vector_cross(t_Vector3 a, t_Vector3 b);

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
void				tocolor(t_RGB *vector, float r, float g, float b);
void				tovec(t_Vector3 *vector, double x, double y, double z);
void				calculate_image(mlx_image_t *image, t_scene *escena);

/// free.c todos los frees de la esttructura

void				free_stting(t_scene *scene);
void				free_pos(t_Vector3 *pos);
void				free_rgb(t_RGB *col);
void				free_material(t_material *mat);
void				free_sphere(t_sphere_prop *props);
void				free_plane(t_plane_prop *props);
void				free_cylinder(t_cyl_prop *props);
void				free_obj(t_scene *scene);
void				free_light(t_scene *scene);
void				free_cam(t_scene *scene);
void				free_escena(t_scene **scene);

/// reserve.c

t_material			*reserve_material(int *error);
void				reserve_ambient(t_scene *scene, int *error);
void				reserve_cam(t_scene *scene, int *error);
t_light				*reserve_light(int *error);

/// reserve_obj.c
t_object			*reserve_obj(int *error);
t_plane_prop		*reserve_plane(int *error);
t_sphere_prop		*reserve_sphere(int *error);
t_cyl_prop			*reserve_cyl(int *error);

/// reserve_utils.c
t_RGB*				reserve_rgb(int *error);
t_Vector3			*reserve_vector(int *error);

// calculate2.c
unsigned int		shade(t_Intersection inter, t_Vector3 ray_dir,
						t_scene *escena, int light);
t_Vector3			create_cam_ray(float px_camera, float py_camera,
						t_scene *escena);
void				calculate_image(mlx_image_t *image, t_scene *escena);

// callculate.c
unsigned int		get_intersection(t_object *obj, t_Vector3 ray_origin,
						t_Vector3 ray_dir, float *dist);
int					check_light(t_object *scene, t_Vector3 cam_origin,
						t_Vector3 ray_dir, float min_dist, t_Vector3 light_pos);
void				set_inter(t_Intersection *inter, float dist,
						unsigned int color, t_object *obj);
t_Vector3			reflect(t_Vector3 I, t_Vector3 N);
int					check_coll(t_Vector3 ray_dir, t_scene *escena,
						t_object *obj);

// color.c
t_RGB				rgba_to_rgb(unsigned int color);
unsigned int		rgb_to_rgba(t_RGB rgb);
unsigned int		color_merge(unsigned int min_color, t_RGB ambient);
unsigned int		compute_color(t_scene *escena, t_shade shading,
						t_Intersection inter, int light);

// parse.c
int					setlight(t_scene *scene, char **line_split, int *error);
int					setcamera(t_scene *scene, char **line_split, int *error);
void				add_light_scene(t_scene *scene, t_light *light);
int					setlight(t_scene *scene, char **line_split, int *error);

// parse_obj.c

int					setplane(t_scene **scene, char **line_split, int *error);
int					setsphere(t_scene **scene, char **line_split, int *error);
int					setcylinder(t_scene **scene, char **line_split, int *error);
void				parse(t_scene *scene, char *file);

// parse_utils.c
float				ft_atof(char *n);
int					array_len(char **array);
void				set_color(t_RGB *color, char **col_num);
int					is_float_array(char *str);
int					valid_iii(char **str);
int					setambient(t_scene *scene, char **line_split, int *error);

// parse_utils2.c
void				set_pos(t_Vector3 *pos, char **pos_a);
void				set_rot(t_Vector3 *pos, char **pos_a);
int					valid_fff(char **str);
void				set_ambient_col(t_RGB *color, char **col_num, float inte);

// parse_utils3.c
char				**split_fff(char *line_split, int *error, int *i);
char				**split_iii(char *line_split, int *error, int *i);
void				add_to_end(t_scene **scene, t_object *obj);
void				set_options(t_scene *scene, char **line_split, int *error);
void				on_error(t_scene **scene, int *error, int fd);
#endif
