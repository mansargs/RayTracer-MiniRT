/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:51:43 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/22 13:18:23 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include <math.h>

double	plane_intersection_formula(const t_ray *ray, t_vec3 plane_p,
		t_vec3 plane_n)
{
	double	denom;
	double	t;

	denom = vec_dot(ray->direction, plane_n);
	if (fabs(denom) < EPS)
		return (-1.0);
	t = vec_dot(vec_sub(plane_p, ray->origin), plane_n) / denom;
	if (t <= EPS)
		return (-1.0);
	return (t);
}

bool	point_in_disk(t_vec3 p, t_vec3 center, double radius, t_vec3 axis)
{
	t_vec3	diff;
	double	proj;
	t_vec3	perp;

	diff = vec_sub(p, center);
	proj = vec_dot(diff, axis);
	perp = vec_sub(diff, vec_scale(axis, proj));
	return (vec_dot(perp, perp) <= radius * radius + EPS);
}

double	get_min_positive(double t1, double t2)
{
	double	t;

	t = INFINITY;
	if (t1 > 0.0)
		t = t1;
	if (t2 > 0.0 && t2 < t)
		t = t2;
	if (t < INFINITY)
		return (t);
	else
		return (-1.0);
}

t_quad	solve_quadratic(t_quad_coeffs coeffs)
{
	t_quad	result;
	double	disc;
	double	sqrt_disc;

	disc = coeffs.b * coeffs.b - 4.0 * coeffs.a * coeffs.c;
	if (disc < 0)
	{
		result.has_solution = false;
		return (result);
	}
	else
	{
		result.has_solution = true;
		sqrt_disc = sqrt(disc);
		result.t1 = (-coeffs.b - sqrt_disc) / (2.0 * coeffs.a);
		result.t2 = (-coeffs.b + sqrt_disc) / (2.0 * coeffs.a);
	}
	return (result);
}
