/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:33:02 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/26 23:45:36 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include <math.h>

static void	update_nearest(t_hit *nearest, const t_hit *candidate)
{
	if (candidate->is_hit && candidate->t < nearest->t)
		*nearest = *candidate;
}

t_hit	objects_intersection(const t_ray *ray, const t_scene *scene)
{
	t_hit	nearest;
	t_hit	hit;

	nearest = (t_hit){.is_hit = false, .t = INFINITY, .type = NO_OBJECT,
		.object = NULL};
	hit = intersect_all_planes(ray, &scene->planes);
	update_nearest(&nearest, &hit);
	hit = intersect_all_spheres(ray, &scene->spheres);
	update_nearest(&nearest, &hit);
	hit = intersect_all_cylinders(ray, &scene->cylinders);
	update_nearest(&nearest, &hit);
	hit = intersect_all_cones(ray, &scene->cones);
	update_nearest(&nearest, &hit);
	return (nearest);
}
