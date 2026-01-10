/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:28:48 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/10 19:18:28 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "vector.h"
#include <math.h>

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

t_hit intersect_sphere(t_ray* ray, t_sphere* sphere)
{
	t_hit			hit;
	t_quad			solution;
	t_quad_coeffs	coeffs;
	t_vec3			oc;
	double			t;

	hit.is_hit = false;
	oc = vec_sub(ray->origin, sphere->center);
	coeffs.a = vec_dot(ray->direction, ray->direction);
	coeffs.b = 2.0 * vec_dot(oc, ray->direction);
	coeffs.c = vec_dot(oc, oc) - sphere->radius * sphere->radius;
	solution = solve_quadratic(coeffs);
	if (!solution.has_solution)
		return (hit);
	t = get_min_positive(solution.t1, solution.t2);
	if (t <= EPS)
		return (hit);
	hit.is_hit = true;
	hit.t = t;
	hit.point = ray_at(ray, hit.t);
	hit.normal = vec_normalization(vec_sub(hit.point, sphere->center));
	return (hit);
}

t_hit	intersect_all_spheres(t_ray* ray, t_vector* all_spheres)
{
	const t_sphere*	sphere;
	t_hit			current;
	t_hit			nearest;
	size_t			i;

	i = 0;
	nearest.t = INFINITY;
	nearest.is_hit = false;
	nearest.type = SPHERE;
	nearest.object = NULL;
	while (i < all_spheres->size)
	{
		sphere = (t_sphere*) vector_get(all_spheres, i);
		current = intersect_sphere(ray, sphere);
		if (current.is_hit && current.t < nearest.t)
		{
			nearest = current;
			nearest.object = (void*)(sphere);
		}
		++i;
	}
	return (nearest);
}
