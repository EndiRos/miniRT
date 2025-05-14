#include "minirt.h"

int	ray_plane_intersect(t_Vector3 ray_orig, t_Vector3 ray_dir,
		t_plane_prop plane, float *t)
{
	float t_val;
	float denominator;

	t_Vector3 n = vector_normalize(plane.normal);
	denominator = vector_dot(ray_dir, n);
	if (fabsf(denominator) < 1e-6)
		return (0);
	t_val = vector_dot(vector_sub(plane.pos, ray_orig), n) / denominator;
	if (t_val < 0.0001f)
		return (0);
	*t = t_val;
	return (1);
}