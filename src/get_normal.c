#include "minirt.h"

t_Vector3	sphere_normal(t_sphere_prop *sphere, t_Vector3 point)
{
	return (vector_normalize(vector_sub(point, sphere->pos)));
}

t_Vector3	plane_normal(t_plane_prop *plane)
{
	return (vector_normalize(plane->normal));
}