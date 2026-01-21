#include "intersection.h"
#include "vector.h"
#include <math.h>

static double	plane_intersection(const t_ray *ray, t_vec3 plane_p, t_vec3 plane_n)
{
	double	denom;

	denom = vec_dot(ray->direction, plane_n);
	if (fabs(denom) < EPS)
		return (-1.0);
	double t = vec_dot(vec_sub(plane_p, ray->origin), plane_n) / denom;
	if (t <= EPS)
		return (-1.0);
	return (t);
}

static bool point_in_disk(t_vec3 p, t_vec3 center, double radius, t_vec3 axis)
{
	t_vec3 diff;
	double proj;
	t_vec3 perp;

	diff = vec_sub(p, center);
	proj = vec_dot(diff, axis);
	perp = vec_sub(diff, vec_scale(axis, proj));
	return (vec_dot(perp, perp) <= radius * radius + EPS);
}

static void	check_cap(const t_ray *ray, const t_cylinder *cy, t_hit *hit,
	t_vec3 cap_center, t_vec3 cap_normal)
{
	double	t;
	t_vec3	p;

	t = plane_intersection(ray, cap_center, cap_normal);
	if (t <= EPS || t >= hit->t)
		return;
	p = ray_at(ray, t);
	if (!point_in_disk(p, cap_center, cy->radius, cap_normal))
		return;
	hit->is_hit = true;
	hit->t = t;
	hit->point = p;
	hit->normal = cap_normal;
}

void	check_cylinder_roots( const t_ray *ray, const t_cylinder *cy, t_vec3 axis, t_hit *hit, double q[2])
{
	t_vec3	p;
	double	h;

	for (int i = 0; i < 2; i++)
	{
		double t = q[i];
		if (t <= EPS || t >= hit->t)
			continue;
		p = ray_at(ray, t);
		h = vec_dot(vec_sub(p, cy->center), axis);
		if (fabs(h) <= cy->height * 0.5)
		{
			t_vec3 n = vec_sub(vec_sub(p, cy->center), vec_scale(axis, h));
			if (vec_magnitude(n) > EPS)
				*hit = (t_hit){.is_hit = true, .t = t, .point = p, .normal = vec_normalize(n)};
		}
	}
}

void	check_cylinder_body(const t_ray *ray, const t_cylinder *cy, t_vec3 axis, t_hit *hit)
{
	t_quad			q;
	t_quad_coeffs	c;
	t_vec3			oc;

	oc = vec_sub(ray->origin, cy->center);
	c.a = vec_dot(ray->direction, ray->direction)
		- pow(vec_dot(ray->direction, axis), 2);
	c.b = 2 * (vec_dot(oc, ray->direction)
		- vec_dot(oc, axis) * vec_dot(ray->direction, axis));
	c.c = vec_dot(oc, oc)
		- pow(vec_dot(oc, axis), 2)
		- cy->radius * cy->radius;
	q = solve_quadratic(c);
	if (!q.has_solution || c.a < EPS)
		return;
	check_cylinder_roots(ray, cy, axis, hit, (double [2]){q.t1, q.t2});
}


t_hit	cylinder_intersection(const t_ray *ray, const t_cylinder *cy)
{
	t_hit	hit;
	t_vec3	axis;

	hit = (t_hit){.is_hit = false, .t = INFINITY};
	axis = vec_normalize(cy->orientation);
	check_cylinder_body(ray, cy, axis, &hit);
	check_cap(ray, cy, &hit,
		vec_add(cy->center, vec_scale(axis, cy->height * 0.5)), axis);
	check_cap(ray, cy, &hit,
		vec_add(cy->center, vec_scale(axis, -cy->height * 0.5)),
		vec_scale(axis, -1));
	if (hit.is_hit && vec_dot(hit.normal, ray->direction) > 0)
		hit.normal = vec_scale(hit.normal, -1);
	return (hit);
}

t_hit intersect_all_cylinders(const t_ray *ray, const t_vector *cylinders)
{
	t_hit nearest = {0};
	nearest.t = INFINITY;
	nearest.is_hit = false;

	for (size_t i = 0; i < cylinders->size; ++i)
	{
		const t_cylinder *cy =
			(const t_cylinder *)vector_get(cylinders, i);

		t_hit cur = cylinder_intersection(ray, cy);

		if (cur.is_hit && cur.t < nearest.t)
		{
			nearest = cur;
			nearest.type = CYLINDER;
			nearest.object = (void *)cy;
		}
	}
	return nearest;
}
