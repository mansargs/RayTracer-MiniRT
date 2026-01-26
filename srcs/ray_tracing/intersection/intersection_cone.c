/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 23:29:11 by noavetis          #+#    #+#             */
/*   Updated: 2026/01/26 23:55:43 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "vector.h"
#include <math.h>

static void	check_cone_root(const t_cone_ctx *ctx, t_hit *hit, double t)
{
	t_vec3	p;
	double	h;
	t_vec3	cp;
	t_vec3	n;

	if (t <= EPS || t >= hit->t)
		return ;
	p = ray_at(ctx->ray, t);
	cp = vec_sub(p, ctx->cone->center);
	h = vec_dot(cp, ctx->axis);
	if (h < 0 || h > ctx->cone->height)
		return ;
	n = vec_sub(cp, vec_scale(ctx->axis, h * (1.0 + ctx->sin2 / ctx->cos2)));
	if (vec_magnitude(n) <= EPS)
		return ;
	hit->is_hit = true;
	hit->t = t;
	hit->point = p;
	hit->normal = vec_normalize(n);
}

static void	check_cone_body(const t_cone_ctx *ctx, t_hit *hit)
{
	t_quad			q;
	t_quad_coeffs	c;
	t_vec3			oc;
	double			dv;
	double			ocv;

	oc = vec_sub(ctx->ray->origin, ctx->cone->center);
	dv = vec_dot(ctx->ray->direction, ctx->axis);
	ocv = vec_dot(oc, ctx->axis);
	c.a = vec_dot(ctx->ray->direction, ctx->ray->direction) * ctx->cos2
		- dv * dv;
	c.b = 2 * (vec_dot(oc, ctx->ray->direction) * ctx->cos2 - dv * ocv);
	c.c = vec_dot(oc, oc) * ctx->cos2 - ocv * ocv;
	q = solve_quadratic(c);
	if (!q.has_solution)
		return ;
	check_cone_root(ctx, hit, q.t1);
	check_cone_root(ctx, hit, q.t2);
}

static void	check_cone_cap(const t_ray *ray, const t_cone *cone,
	t_vec3 axis, t_hit *hit)
{
	t_vec3	cap_center;
	t_vec3	cap_normal;
	double	cap_radius;
	double	t;
	t_vec3	p;

	cap_center = vec_add(cone->center, vec_scale(axis, cone->height));
	cap_normal = axis;
	cap_radius = cone->height * tan(cone->angle);
	t = plane_intersection_formula(ray, cap_center, cap_normal);
	if (t <= EPS || t >= hit->t)
		return ;
	p = ray_at(ray, t);
	if (!point_in_disk(p, cap_center, cap_radius, cap_normal))
		return ;
	hit->is_hit = true;
	hit->t = t;
	hit->point = p;
	hit->normal = cap_normal;
}

static t_hit	cone_intersect(const t_ray *ray, const t_cone *cone)
{
	t_hit		hit;
	t_cone_ctx	ctx;

	hit.is_hit = false;
	hit.t = INFINITY;
	ctx.ray = ray;
	ctx.cone = cone;
	ctx.axis = vec_normalize(cone->orientation);
	ctx.cos2 = cos(cone->angle) * cos(cone->angle);
	ctx.sin2 = sin(cone->angle) * sin(cone->angle);
	check_cone_body(&ctx, &hit);
	check_cone_cap(ray, cone, ctx.axis, &hit);
	if (hit.is_hit && vec_dot(hit.normal, ray->direction) > 0)
		hit.normal = vec_scale(hit.normal, -1);
	return (hit);
}

t_hit	intersect_all_cones(const t_ray *ray, const t_vector *cones)
{
	t_hit			nearest;
	t_hit			curr;
	const t_cone	*cone;
	size_t			i;

	nearest = (t_hit){.is_hit = false, .t = INFINITY,
		.type = NO_OBJECT, .object = NULL };
	i = 0;
	while (i < cones->size)
	{
		cone = (const t_cone *)vector_get(cones, i);
		curr = cone_intersect(ray, cone);
		if (curr.is_hit && curr.t < nearest.t)
		{
			nearest = curr;
			nearest.type = CONE;
			nearest.object = (void *)cone;
		}
		++i;
	}
	return (nearest);
}
