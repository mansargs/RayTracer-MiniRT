/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinders.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:13:28 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/22 13:15:00 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "vector.h"
#include <math.h>

static void	check_cap(const t_ray *ray, const t_cap *cap, t_hit *hit)
{
	double	t;
	t_vec3	p;

	t = plane_intersection_formula(ray, cap->center, cap->normal);
	if (t <= EPS || t >= hit->t)
		return ;
	p = ray_at(ray, t);
	if (!point_in_disk(p, cap->center, cap->radius, cap->normal))
		return ;
	hit->is_hit = true;
	hit->t = t;
	hit->point = p;
	hit->normal = cap->normal;
}

static void	check_cylinder_root(const t_cyl_ctx *ctx, t_hit *hit, double t)
{
	t_vec3	p;
	double	h;
	t_vec3	n;

	if (t <= EPS || t >= hit->t)
		return ;
	p = ray_at(ctx->ray, t);
	h = vec_dot(vec_sub(p, ctx->cy->center), ctx->axis);
	if (fabs(h) > ctx->cy->height * 0.5)
		return ;
	n = vec_sub(vec_sub(p, ctx->cy->center), vec_scale(ctx->axis, h));
	if (vec_magnitude(n) <= EPS)
		return ;
	hit->is_hit = true;
	hit->t = t;
	hit->point = p;
	hit->normal = vec_normalize(n);
}

static void	check_cylinder_body(const t_ray *ray, const t_cylinder *cy,
	t_vec3 axis, t_hit *hit)
{
	t_quad			q;
	t_quad_coeffs	c;
	t_vec3			oc;
	t_cyl_ctx		ctx;

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
		return ;
	ctx.ray = ray;
	ctx.cy = cy;
	ctx.axis = axis;
	check_cylinder_root(&ctx, hit, q.t1);
	check_cylinder_root(&ctx, hit, q.t2);
}

static t_hit	cylinder_intersection(const t_ray *ray, const t_cylinder *cy)
{
	t_hit	hit;
	t_vec3	axis;
	t_cap	cap;

	hit.is_hit = false;
	hit.t = INFINITY;
	axis = vec_normalize(cy->orientation);
	check_cylinder_body(ray, cy, axis, &hit);
	cap.radius = cy->radius;
	cap.center = vec_add(cy->center, vec_scale(axis, cy->height * 0.5));
	cap.normal = axis;
	check_cap(ray, &cap, &hit);
	cap.center = vec_add(cy->center, vec_scale(axis, -cy->height * 0.5));
	cap.normal = vec_scale(axis, -1);
	check_cap(ray, &cap, &hit);
	if (hit.is_hit && vec_dot(hit.normal, ray->direction) > 0)
		hit.normal = vec_scale(hit.normal, -1);
	return (hit);
}

t_hit	intersect_all_cylinders(const t_ray *ray, const t_vector *cylinders)
{
	t_hit				nearest;
	t_hit				cur;
	const t_cylinder	*cy;
	size_t				i;

	nearest = (t_hit){0};
	nearest.t = INFINITY;
	nearest.is_hit = false;
	i = 0;
	while (i < cylinders->size)
	{
		cy = (const t_cylinder *)vector_get(cylinders, i);
		cur = cylinder_intersection(ray, cy);
		if (cur.is_hit && cur.t < nearest.t)
		{
			nearest = cur;
			nearest.type = CYLINDER;
			nearest.object = (void *)cy;
		}
		++i;
	}
	return (nearest);
}
