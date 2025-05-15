/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hardcoding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:05:47 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/15 13:50:56 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_scene *harcoding(void)
{
    t_scene *escena;
    t_camera *cam;
    t_light *light;
    t_object *sphere_obj;
    t_object *plane_obj;

    // Allocate scene
    escena = (t_scene *)malloc(sizeof(t_scene));

    // ----- Camera -----
    cam = (t_camera *)malloc(sizeof(t_camera));
    cam->fov = 60.0f;
    tovec(&cam->pos, 0, 0, 0);         // Camera at origin
    tovec(&cam->rot, 0, 0, 0);         // Looking along +Z
    escena->cam = cam;

    // ----- Light -----
    light = (t_light *)malloc(sizeof(t_light));
    tocolor(&light->color, 1.0f, 1.0f, 1.0f);     // White light
    tovec(&light->pos, 0, 5, -5);                 // Above and behind camera
    light->intensity = 1.0f;
    escena->light = light;

    // ----- Sphere Object -----
    sphere_obj = (t_object *)malloc(sizeof(t_object));
    sphere_obj->obj_type = SPHERE;
    sphere_obj->next = NULL;

    t_sphere_prop *sphere = (t_sphere_prop *)malloc(sizeof(t_sphere_prop));
    tovec(&sphere->pos, 0, 0, 5);             // Sphere 5 units ahead
    sphere->radius = 2.0f;

    t_material *sphere_mat = (t_material *)malloc(sizeof(t_material));
    tocolor(&sphere_mat->difuse, 255, 0, 0);       // Red
    tocolor(&sphere_mat->specular, 128, 128, 128);
    tocolor(&sphere_mat->reflexion, 0, 0, 0);
    tocolor(&sphere_mat->refraction, 0, 0, 0);
    sphere->material = sphere_mat;

    sphere_obj->props = (void *)sphere;

    // ----- Plane Object -----
    plane_obj = (t_object *)malloc(sizeof(t_object));
    plane_obj->obj_type = PLANE;
    plane_obj->next = NULL;

    t_plane_prop *plane = (t_plane_prop *)malloc(sizeof(t_plane_prop));
    tovec(&plane->pos, 0, 0, 5);               // Plane 1 unit in front of sphere
    tovec(&plane->normal, 0, 0, -1);           // Facing toward camera

    t_material *plane_mat = (t_material *)malloc(sizeof(t_material));
    tocolor(&plane_mat->difuse, 0, 255, 0);         // Green
    tocolor(&plane_mat->specular, 128, 128, 128);
    tocolor(&plane_mat->reflexion, 0, 0, 0);
    tocolor(&plane_mat->refraction, 0, 0, 0);
    plane->material = plane_mat;

    plane_obj->props = (void *)plane;

    // Link objects: sphere -> plane
    sphere_obj->next = plane_obj;
    escena->objects = sphere_obj;

    return escena;
}

/*
int main(int argc, char **argv)
{
	(void)argc;  // Ignora el parámetro argc
    (void)argv;
	t_scene *escena;
	
	escena = harcoding();

	printf("objeto1 %u , objeto1 %u", escena->objects->obj_type, escena->objects->next->obj_type);
	if (escena->objects->obj_type == SPHERE)
		(printf ("esfera,  %f",((t_sphere_prop *)escena->objects->props)->radius));
	if (escena->objects->next->obj_type == PLANE)
		(printf ("plano"));
	return (0);
} */