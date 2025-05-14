/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hardcoding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:05:47 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/14 12:57:13 by enetxeba         ###   ########.fr       */
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
    t_object *tmp_obj;
	

    // Asignación de la cámara
    cam = (t_camera *)malloc(sizeof(t_camera));
    cam->fov = 45;
    tovec(&cam->pos, 5.4848, 0, 2.227);
    tovec(&cam->rot, 90, 0, 100.17);

    // Asignación de la luz
    light = (t_light *)malloc(sizeof(t_light));
    tocolor(&light->color, 1.0, 0.0, 0.0);
    tovec(&light->pos, 5.46, -9.1, 8.19);
    light->intensity = 1.0;

    // Asignación de la escena
    escena = (t_scene *)malloc(sizeof(t_scene));
    escena->cam = cam;
    escena->light = light;
    escena->objects = NULL;  // Asegúrate de inicializar la lista de objetos como NULL

    // Crear primer objeto (esfera)
    tmp_obj = (t_object *)malloc(sizeof(t_object));
    tmp_obj->obj_type = SPHERE;

    // Propiedades de la esfera
    t_sphere_prop *tmp_s = (t_sphere_prop *)malloc(sizeof(t_sphere_prop));
    tovec(&tmp_s->pos, -1.86, 0.04, 2.385);
    tmp_s->radius = 0.352;
    t_material *mat = (t_material *)malloc(sizeof(t_material));
    tocolor(&mat->difuse, 255, 0, 0);
    tocolor(&mat->specular, 128, 128, 128);
    tocolor(&mat->reflexion, 0, 0, 0);
    tocolor(&mat->refraction, 0, 0, 0);
    tmp_s->material = mat;

    tmp_obj->props = (void *)tmp_s; // Asignar propiedades de la esfera a props
     // Enlazar el primer objeto de la escena
	escena->objects = tmp_obj;
    // Crear segundo objeto (plano)
    tmp_obj = (t_object *)malloc(sizeof(t_object));
    tmp_obj->next = NULL;
    tmp_obj->obj_type = PLANE;

    // Propiedades del plano
    t_plane_prop *tmp_p = (t_plane_prop *)malloc(sizeof(t_plane_prop));
    tovec(&tmp_p->pos, -1.86, 0.04, 2.385);
    tovec(&tmp_p->normal, 0, 0, 1);
    mat = (t_material *)malloc(sizeof(t_material));
    tocolor(&mat->difuse, 28, 128, 35);
    tocolor(&mat->specular, 128, 128, 128);
    tocolor(&mat->reflexion, 0, 0, 0);
    tocolor(&mat->refraction, 0, 0, 0);
    tmp_p->material = mat;

    tmp_obj->props = (void *)tmp_p; // Asignar propiedades del plano a props
	escena->objects->next = tmp_obj;
	return (escena); // Enlazar el segundo objeto (plano) al primero (esfera)
}

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
} 