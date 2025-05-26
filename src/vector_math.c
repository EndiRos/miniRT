#include "minirt.h"

t_Vector3	vector_add(t_Vector3 a, t_Vector3 b)
{
	return ((t_Vector3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_Vector3	vector_sub(t_Vector3 a, t_Vector3 b)
{
	return ((t_Vector3){a.x - b.x, a.y - b.y, a.z - b.z});
}

float	vector_dot(t_Vector3 a, t_Vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	vector_magnitude(t_Vector3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_Vector3	vector_normalize(t_Vector3 v)
{
	float	mag;

	mag = vector_magnitude(v);
	if (mag == 0.0f)
		return ((t_Vector3){0, 0, 0});
	return ((t_Vector3){v.x / mag, v.y / mag, v.z / mag});
}

t_Vector3	vector_scale(t_Vector3 v, float scalar)
{
	return ((t_Vector3){v.x * scalar, v.y * scalar, v.z * scalar});
}

t_Vector3 vector_cross(t_Vector3 a, t_Vector3 b)
{
    return (t_Vector3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}
