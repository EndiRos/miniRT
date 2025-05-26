/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:16:36 by imugica-          #+#    #+#             */
/*   Updated: 2025/05/26 10:40:58 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
int	main(int c, char **args)
{
	t_Vector3	ray_origin;
	t_Vector3	ray_dir;
	t_cyl_prop	cyl;
	float		t;

	ray_origin = {0, 0, 0};
	ray_dir = vector_normalize((t_Vector3){0, 0, 1});
	cyl.pos = (t_Vector3){0, 0, 5};
	cyl.rot = vector_normalize((t_Vector3){1, 1, 1});
	cyl.radius = 1.0f;
	cyl.height = 4.0f;
	if (ray_cylinder_intersect(ray_origin, ray_dir, cyl, &t)) {
		printf("Intersection at t = %f\n", t);
	} else {
		printf("No intersection\n");
	}
	return (0);
}
 */

 void	tovec(t_Vector3 *vector, double x, double y ,double z)
 {
	 vector->x = x;
	 vector->y = y;
	 vector->z = z;
 }
 void	tocolor(t_RGB *vector, float r, float g ,float b)
 {
	 vector->r = r;
	 vector->g = g;
	 vector->b = b;
 }

void	key_hook(struct mlx_key_data keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(mlx);
	}
}

unsigned int	get_intersection(t_object *obj, t_Vector3 ray_origin,
		t_Vector3 ray_dir, float *dist)
{
	unsigned int	color;

	color = 0;
	if (obj->obj_type == SPHERE)
		color = ray_sphere_intersect(ray_origin, ray_dir,
				*(t_sphere_prop *)obj->props, dist);
	else if (obj->obj_type == CYLINDER)
		color = ray_cylinder_intersect(ray_origin, ray_dir,
				*(t_cyl_prop *)obj->props, dist);
	else if (obj->obj_type == PLANE)
		color = ray_plane_intersect(ray_origin, ray_dir,
				*(t_plane_prop *)obj->props, dist);
	return (color);
}

int	check_light(t_object *scene, t_Vector3 cam_origin, t_Vector3 ray_dir,
		float min_dist, t_Vector3 light_pos)
{
	t_Vector3	intersection_point;
	t_Vector3	light_dir;
	float		light_distance;
	t_object	*obj;
	float		shadow_dist;

	intersection_point = vector_add(cam_origin, vector_scale(ray_dir,
				min_dist));
	light_dir = vector_sub(light_pos, intersection_point);
	light_distance = vector_magnitude(light_dir);
	light_dir = vector_normalize(light_dir);
	obj = scene;
	while (obj)
	{
		shadow_dist = FLT_MAX;
		get_intersection(obj, intersection_point, light_dir, &shadow_dist);
		if (shadow_dist > 0.001f && shadow_dist < light_distance)
		{
			return (0);
		}
		obj = obj->next;
	}
	return (1);
}

unsigned int	color_merge(unsigned int min_color, t_RGB ambient)
{
	t_RGB	base_rgb;

	base_rgb = rgba_to_rgb(min_color);
	base_rgb.r = (base_rgb.r * ambient.r) / 255;
	base_rgb.g = (base_rgb.g * ambient.g) / 255;
	base_rgb.b = (base_rgb.b * ambient.b) / 255;
	return (rgb_to_rgba(base_rgb));
}

void	set_inter(t_Intersection *inter, float dist, unsigned int color,
		t_object *obj)
{
	inter->min_dist = dist;
	inter->min_color = color;
	inter->object = obj;
}

t_Vector3	reflect(t_Vector3 I, t_Vector3 N)
{
	float	dot_product;

	dot_product = vector_dot(I, N);
	return (vector_sub(I, vector_scale(N, 2.0f * dot_product)));
}
unsigned int	compute_color(t_scene *escena, t_shade shading,
		t_Intersection inter, int light)
{
	t_RGB base_rgb; //
	float diffuse;  //
	float specular; //
	shading.light_dir = vector_normalize(vector_sub(*escena->light->pos,
				shading.hit_point));
	shading.view_dir = vector_normalize(vector_sub(*escena->cam->pos,
				shading.hit_point));
	diffuse = fmaxf(0.0f, vector_dot(shading.normal, shading.light_dir))
		* escena->light->intensity;
	shading.reflected = reflect(vector_scale(shading.light_dir, -1),
			shading.normal);
	specular = powf(fmaxf(vector_dot(shading.reflected, shading.view_dir),
				0.0f), 32.0f);
	specular *= escena->light->intensity * light;
	base_rgb = rgba_to_rgb(inter.min_color);
	base_rgb.r = fminf(base_rgb.r * diffuse + specular * 255.0f
			+ escena->seting->ambient_col->r, 255);
	base_rgb.g = fminf(base_rgb.g * diffuse + specular * 255.0f
			+ escena->seting->ambient_col->g, 255);
	base_rgb.b = fminf(base_rgb.b * diffuse + specular * 255.0f
			+ escena->seting->ambient_col->b, 255);
	return (rgb_to_rgba(base_rgb));
}

unsigned int	shade(t_Intersection inter, t_Vector3 ray_dir, t_scene *escena,
		int light)
{
	t_shade	shading;

	shading.hit_point = vector_add(*escena->cam->pos, vector_scale(ray_dir,
				inter.min_dist));
	shading.normal = vector_normalize((t_Vector3){0, 0, 1});
	if (inter.object->obj_type == SPHERE)
		shading.normal = vector_normalize(sphere_normal((t_sphere_prop *)inter.object->props,
					shading.hit_point));
	else if (inter.object->obj_type == PLANE)
		shading.normal = vector_normalize(plane_normal((t_plane_prop *)inter.object->props));
	else if (inter.object->obj_type == CYLINDER)
		shading.normal = vector_normalize(cylinder_normal((t_cyl_prop *)inter.object->props,
					shading.hit_point));
	// compute_color(shading);
	return (compute_color(escena, shading, inter, light));
}

int	check_coll(t_Vector3 ray_dir, t_scene *escena, t_object *obj)
{
	t_Intersection	inter;
	float			temp_dist;
	unsigned int	temp_color;
	int				light;

	inter.min_dist = FLT_MAX;
	inter.min_color = 0;
	inter.object = NULL;
	light = 0;
	while (obj)
	{
		temp_dist = FLT_MAX;
		temp_color = get_intersection(obj, *escena->cam->pos, ray_dir,
				&temp_dist);
		if (temp_dist < inter.min_dist)
			set_inter(&inter, temp_dist, temp_color, obj);
		obj = obj->next;
	}
	light = check_light(escena->objects, *escena->cam->pos, ray_dir,
			inter.min_dist, *escena->light->pos);
	if (!light)
		inter.min_color = color_merge(inter.min_color,
				*escena->seting->ambient_col);
	if (inter.object)
		inter.min_color = shade(inter, ray_dir, escena, light);
	return (inter.min_color);
}

t_Vector3	rotate_vector(t_Vector3 v, t_Vector3 rot)
{
	t_Vector3	sin;
	t_Vector3	cos;
	t_Vector3	v1;
	t_Vector3	v2;
	t_Vector3	v3;

	tovec(&sin, sinf(rot.x), sinf(rot.y), sinf(rot.z));
	tovec(&cos, cosf(rot.x), cosf(rot.y), cosf(rot.z));
	tovec(&v1, v.x, v.y * cos.x - v.z * sin.x, v.y * sin.x + v.z * cos.x);
	tovec(&v2, v1.x * cos.y + v1.z * sin.y, v1.y, -v1.x * sin.y + v1.z * cos.y);
	tovec(&v3, v2.x * cos.z - v2.y * sin.z, v2.x * sin.z + v2.y * cos.z, v2.z);
	return (v3);
}

t_Vector3	create_cam_ray(float px_camera, float py_camera, t_scene *escena)
{
	t_Vector3	ray_cam_dir;
	t_Vector3	ray_world_dir;

	tovec(&ray_cam_dir, px_camera, py_camera, 1.0f);
	ray_world_dir = rotate_vector(ray_cam_dir, *escena->cam->rot);
	ray_world_dir = vector_normalize(ray_world_dir);
	return (ray_world_dir);
}

void	calculate_image(mlx_image_t *image, t_scene *escena)
{
	unsigned int	px;
	unsigned int	py;
	unsigned int	color;
	float			px_camera;
	float			py_camera;

	px = 0;
	py = 0;
	escena->cam->aspect_ratio = (float)image->width / (float)image->height;
	//escena->cam->fov = escena->cam->fov * (M_PI / 180.0f);
	//escena->cam->scale = tanf(escena->cam->fov / 2.0f);
	while (py < image->height)
	{
		while (px < image->width)
		{
			px_camera = (2.0f * (px + 0.5f) / image->width - 1.0f)
				* escena->cam->aspect_ratio * escena->cam->scale;
			py_camera = (1.0f - 2.0f * (py + 0.5f) / image->height)
				* escena->cam->scale;
			color = check_coll(create_cam_ray(px_camera, py_camera, escena),
					escena, escena->objects);
			mlx_put_pixel(image, px++, py, color);
		}
		px = 0;
		py++;
	}
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_scene		*escena;

	//escena = harcoding();
    
	
    escena = (t_scene *) malloc (sizeof (t_scene));
	ft_memset (escena, 0 , sizeof(t_scene));
    parse(escena, argv[1]);
	(void)argc;
	if (!(mlx = mlx_init(1920, 1080, "tXuperRT", true)))
	{
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	if (!(image = mlx_new_image(mlx, 1920, 1080)))
	{
		mlx_close_window(mlx);
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	calculate_image(image, escena);
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_escena(&escena);
	return (0);
}
