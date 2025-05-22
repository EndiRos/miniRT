/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hardcoding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imugica- <imugica-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:05:47 by enetxeba          #+#    #+#             */
/*   Updated: 2025/05/22 11:52:14 by imugica-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



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
    tovec(&cam->pos, 6, 2, -4);
    tovec(&cam->rot, 0, 0, 0); // 90 degrees pitch to look down
    escena->cam = cam;

    // ----- Light -----
    light = (t_light *)malloc(sizeof(t_light));
    tocolor(&light->color, 1.0f, 1.0f, 1.0f);     // White light
    tovec(&light->pos, 3, 3, 1); 
    light->intensity = 1.0f;
    escena->light = light;

    // ----- Sphere Object -----
    sphere_obj = (t_object *)malloc(sizeof(t_object));
    sphere_obj->obj_type = SPHERE;
    sphere_obj->next = NULL;

    t_sphere_prop *sphere = (t_sphere_prop *)malloc(sizeof(t_sphere_prop));
    tovec(&sphere->pos, 0, -1, 4.5);             // Sphere 5 units ahead
    sphere->radius = 1.5f;

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
    tovec(&plane->pos, 0, -2, 3.01);               // Plane 1 unit in front of sphere
    tovec(&plane->normal, 0, 1, 0);           // Facing toward camera

    t_material *plane_mat = (t_material *)malloc(sizeof(t_material));
    tocolor(&plane_mat->difuse, 50, 150, 90);    
         // Green
    tocolor(&plane_mat->specular, 128, 128, 128);
    tocolor(&plane_mat->reflexion, 0, 0, 0);
    tocolor(&plane_mat->refraction, 0, 0, 0);
    plane->material = plane_mat;

    plane_obj->props = (void *)plane;

    

    // Link objects: sphere -> plane
    sphere_obj->next = plane_obj;
    escena->objects = sphere_obj;

    // ----- Sphere Object -----
    sphere_obj = (t_object *)malloc(sizeof(t_object));
    sphere_obj->obj_type = SPHERE;
    sphere_obj->next = NULL;

    sphere = (t_sphere_prop *)malloc(sizeof(t_sphere_prop));
    tovec(&sphere->pos, 2, -1, 4.5);             // Sphere 5 units ahead
    sphere->radius = 1.5f;

    sphere_mat = (t_material *)malloc(sizeof(t_material));
    tocolor(&sphere_mat->difuse, 0, 0, 255);       // Red
    tocolor(&sphere_mat->specular, 128, 128, 128);
    tocolor(&sphere_mat->reflexion, 0, 0, 0);
    tocolor(&sphere_mat->refraction, 0, 0, 0);
    sphere->material = sphere_mat;

    sphere_obj->props = (void *)sphere;

    plane_obj->next = sphere_obj;

    // ----- Ambient Light Settings -----
    t_settings *settings = (t_settings *)malloc(sizeof(t_settings));
    tocolor(&settings->ambient_col, (50 * 1.0f) , (50 * 1.0f), 50*1.0f);  // Yellow ambient light
    settings->intensity = 1.0f;                    // You can adjust this intensity as needed
    escena->seting = settings;

        // ----- Cylinder Object -----
        t_object *cyl_obj = (t_object *)malloc(sizeof(t_object));
        cyl_obj->obj_type = CYLINDER;
        cyl_obj->next = NULL;
    
        t_cyl_prop *cylinder = (t_cyl_prop *)malloc(sizeof(t_cyl_prop));
        tovec(&cylinder->pos, 1, 0, 5);              // Position it in the scene
        tovec(&cylinder->rot, 0, 1, 0);              // Vertical orientation (Y-axis)
        cylinder->rot = vector_normalize(cylinder->rot);
        cylinder->radius = 1.0f;
        cylinder->height = 7.0f;
    
        t_material *cyl_mat = (t_material *)malloc(sizeof(t_material));
        tocolor(&cyl_mat->difuse, 0, 255, 0);       // Yellow
        tocolor(&cyl_mat->specular, 128, 128, 128);
        tocolor(&cyl_mat->reflexion, 0, 0, 0);
        tocolor(&cyl_mat->refraction, 0, 0, 0);
        cyl_mat->IOR = 1.0f;
    
        cylinder->material = cyl_mat;
        cyl_obj->props = (void *)cylinder;
        t_Vector3 dir_to_cam = vector_sub(escena->cam->pos, cylinder->pos);
        dir_to_cam = vector_normalize(dir_to_cam);
        
        // Rotate it slightly around the Y axis
        float angle = M_PI / 12.0f;  // 15 degrees
        float sin_a = sinf(angle);
        float cos_a = cosf(angle);
        
        t_Vector3 rotated_dir;
        rotated_dir.x = cos_a * dir_to_cam.x + sin_a * dir_to_cam.z;
        rotated_dir.y = dir_to_cam.y;
        rotated_dir.z = -sin_a * dir_to_cam.x + cos_a * dir_to_cam.z;
        
        // Assign the rotated direction to cylinder's rotation
        //cylinder->rot = vector_normalize(rotated_dir);
    
       sphere_obj->next = cyl_obj;

           // ----- Sphere Object -----
    sphere_obj = (t_object *)malloc(sizeof(t_object));
    sphere_obj->obj_type = SPHERE;
    sphere_obj->next = NULL;

    sphere = (t_sphere_prop *)malloc(sizeof(t_sphere_prop));
    tovec(&sphere->pos, 1, 3.3, 5);             // Sphere 5 units ahead
    sphere->radius = 1.1f;

    sphere_mat = (t_material *)malloc(sizeof(t_material));
    tocolor(&sphere_mat->difuse, 0, 0, 255);       // Red
    tocolor(&sphere_mat->specular, 128, 128, 128);
    tocolor(&sphere_mat->reflexion, 0, 0, 0);
    tocolor(&sphere_mat->refraction, 0, 0, 0);
    sphere->material = sphere_mat;

    sphere_obj->props = (void *)sphere;

    cyl_obj->next = sphere_obj;

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