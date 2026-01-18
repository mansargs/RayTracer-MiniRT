/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_spheres.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:17:50 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 01:18:29 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "intersection.h"
#include "vector.h"
#include <math.h>

static void	set_sphere_hit(t_hit *hit, double t, const t_ray *ray,
				const t_sphere *sphere)
{
	t_vec3	center_to_point;

	hit->is_hit = true;
	hit->t = t;
	hit->point = ray_at(ray, t);
	center_to_point = vec_sub(hit->point, sphere->center);
	hit->normal = vec_normalize(center_to_point);
}

static t_hit	sphere_intersection(const t_ray *ray, const t_sphere *sphere)
{
	t_hit			hit;
	t_vec3			oc;
	t_quad_coeffs	coeffs;
	t_quad			solution;
	double			t;

	hit = (t_hit){0};
	hit.is_hit = false;
	hit.t = INFINITY;
	oc = vec_sub(ray->origin, sphere->center);
	coeffs.a = vec_dot(ray->direction, ray->direction);
	coeffs.b = 2.0 * vec_dot(oc, ray->direction);
	coeffs.c = vec_dot(oc, oc) - sphere->radius * sphere->radius;
	solution = solve_quadratic(coeffs);
	if (!solution.has_solution)
		return (hit);
	t = get_min_positive(solution.t1, solution.t2);
	if (t < EPS)
		return (hit);
	set_sphere_hit(&hit, t, ray, sphere);
	return (hit);
}

t_hit	intersect_all_spheres(const t_ray *ray, const t_vector *spheres)
{
	t_hit			nearest;
	t_hit			current;
	const t_sphere	*sphere;
	size_t			i;

	nearest = (t_hit){.is_hit = false, .t = INFINITY,
		.type = NO_OBJECT, .object = NULL};
	i = 0;
	while (i < spheres->size)
	{
		sphere = (const t_sphere *)vector_get(spheres, i);
		current = sphere_intersection(ray, sphere);
		if (current.is_hit && current.t < nearest.t)
		{
			nearest = current;
			nearest.type = SPHERE;
			nearest.object = (void *)sphere;
		}
		++i;
	}
	return (nearest);
}
