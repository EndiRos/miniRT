#include "minirt.h"

int	cyl_quadratic(t_Vector3 ray_orig, t_Vector3 ray_dir, t_cyl_prop cyl,
		float *t_out)
{
	t_Vector3	ca;
	t_Vector3	oc;
	t_Vector3	d_cross_v;
	t_Vector3	oc_cross_v;

	ca = vector_normalize(*cyl.rot);
	oc = vector_sub(ray_orig, *cyl.pos);
	d_cross_v = vector_sub(ray_dir, vector_scale(ca, vector_dot(ray_dir, ca)));
	oc_cross_v = vector_sub(oc, vector_scale(ca, vector_dot(oc, ca)));
	if (!quadratic(vector_dot(d_cross_v, d_cross_v), 2.0f
			* vector_dot(d_cross_v, oc_cross_v), vector_dot(oc_cross_v,
				oc_cross_v) - cyl.radius * cyl.radius, t_out))
		return (0);
	return (1);
}

int	cyl_face_coll(t_Vector3 ray_orig, t_Vector3 ray_dir, t_cyl_prop cyl,
		float *t_out)
{
	t_Vector3	p;
	t_Vector3	pc;
	float		proj;
	float		half_height;
	float		epsilon;

	half_height = cyl.height * 0.5f;
	epsilon = 1e-4f;
	p = vector_add(ray_orig, vector_scale(ray_dir, *t_out));
	pc = vector_sub(p, *cyl.pos);
	proj = vector_dot(pc, *cyl.rot);
	if (proj >= -half_height - epsilon && proj <= half_height + epsilon)
		return (1);
	return (0);
}

int	cyl_top_bot_coll(t_Vector3 ray_orig, t_Vector3 ray_dir, t_cyl_prop cyl,
		float *t_out)
{
	int		i;
	int		hit;
	float	epsilon;

	t_Vector3 cap_center, oc_to_cap, p_cap, pc_cap;
	float denom, t, best_t = *t_out;
	hit = 0;
	epsilon = 1e-4f;
	for (i = 0; i < 2; i++)
	{
		cap_center = vector_add(*cyl.pos, vector_scale(*cyl.rot, (i == 0 ?
						-0.5f : 0.5f) * cyl.height));
		oc_to_cap = vector_sub(cap_center, ray_orig);
		denom = vector_dot(ray_dir, *cyl.rot);
		if (fabsf(denom) < 1e-6f)
			continue ;
		t = vector_dot(oc_to_cap, *cyl.rot) / denom;
		if (t < 0.001f || t >= best_t)
			continue ;
		p_cap = vector_add(ray_orig, vector_scale(ray_dir, t));
		pc_cap = vector_sub(p_cap, cap_center);
		if (vector_dot(pc_cap, pc_cap) <= cyl.radius * cyl.radius + epsilon)
		{
			best_t = t;
			hit = 1;
		}
	}
	if (hit)
		return (*t_out = best_t, 1);
	return (0);
}

void	save_hit(int *hit, float *best_t, float t)
{
	*hit = 1;
	*best_t = t;
}

unsigned int	ray_cylinder_intersect(t_Vector3 ray_orig, t_Vector3 ray_dir,
		t_cyl_prop cyl, float *t_out)
{
	int		hit;
	float	t;
	float	best_t;

	hit = 0;
	best_t = *t_out;
	if (cyl_quadratic(ray_orig, ray_dir, cyl, &t))
	{
		if (cyl_face_coll(ray_orig, ray_dir, cyl, &t) && t > 0.001f
			&& t < best_t)
			save_hit(&hit, &best_t, t);
	}
	t = *t_out;
	if (cyl_top_bot_coll(ray_orig, ray_dir, cyl, &t) && t > 0.001f
		&& t < best_t)
		save_hit(&hit, &best_t, t);
	if (hit)
	{
		*t_out = best_t;
		return (rgb_to_rgba(*cyl.material->difuse));
	}
	return (255);
}
