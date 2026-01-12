/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interspection_planes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:10:36 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/12 16:15:40 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "minirt.h"
#include "vector.h"
#include <math.h>

static t_hit	intersect_plane(const t_ray *ray, const t_plane *plane)
{
	t_hit	hit;
	t_vec3	n;
	double	nd;
	double	t;

	hit = t_hit{0};
	hit.is_hit = false;
	hit.t = INFINITY;
	n = vec_normalization(plane->orientation);
	nd = vec_dot(ray->direction, n);
	if (fabs(nd) < EPS)
		return (hit);
	t = vec_dot(n, vec_sub(plane->position, ray->origin)) / nd;
	if (t < EPS)
		return (hit);
	hit.is_hit = true;
	hit.t = t;
	hit.normal = n;
	hit.point = ray_at(ray, t);
	if (vec_dot(hit.normal, ray->direction) > 0)
		hit.normal = vec_scale(hit.normal, -1.0);
	return (hit);
}

t_hit	intersect_all_planes(const t_ray *ray, const t_vector *planes)
{
	t_hit			nearest;
	t_hit			curr;
	const t_plane	*plane;
	size_t			i;

	nearest = (t_hit){.is_hit = false, .t = INFINITY,
		.type = NO_OBJECT, .object = NULL };
	i = 0;
	while (i < planes->size)
	{
		plane = (const t_plane *)vector_get(planes, i);
		curr = intersect_plane(ray, plane);
		if (curr.is_hit && curr.t < nearest.t)
		{
			nearest = curr;
			nearest.type = PLANE;
			nearest.object = (void *)plane;
		}
		++i;
	}
	return (nearest);
}
