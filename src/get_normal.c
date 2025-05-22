#include "minirt.h"

t_Vector3	sphere_normal(t_sphere_prop *sphere, t_Vector3 point)
{
	return (vector_normalize(vector_sub(point, *sphere->pos)));
}

t_Vector3	plane_normal(t_plane_prop *plane)
{
	return (vector_normalize(*plane->rot));
}

t_Vector3	cylinder_normal(t_cyl_prop *cyl, t_Vector3 point)
{
	t_Vector3	ca = vector_normalize(*cyl->rot);
	t_Vector3	cp = vector_sub(point, *cyl->pos);
	float		proj_len = vector_dot(cp, ca);

	// Clamp projection to avoid small overshoots due to floating point error
	float half_height = cyl->height * 0.5f;
	float epsilon = 1e-2f; // larger epsilon for safer cap detection

	// Top cap
	if (proj_len >= half_height - epsilon)
	{
		t_Vector3 cap_center = vector_add(*cyl->pos, vector_scale(ca, half_height));
		t_Vector3 diff = vector_sub(point, cap_center);
		if (vector_dot(diff, diff) <= (cyl->radius + epsilon) * (cyl->radius + epsilon))
			return (ca);
	}

	// Bottom cap
	if (proj_len <= -half_height + epsilon)
	{
		t_Vector3 cap_center = vector_add(*cyl->pos, vector_scale(ca, -half_height));
		t_Vector3 diff = vector_sub(point, cap_center);
		if (vector_dot(diff, diff) <= (cyl->radius + epsilon) * (cyl->radius + epsilon))
			return (vector_scale(ca, -1));
	}

	// Side surface
	t_Vector3 proj = vector_scale(ca, proj_len);
	t_Vector3 normal = vector_sub(cp, proj);
	return (vector_normalize(normal));
}