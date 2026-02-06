/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deactivate_checkerboard.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 23:53:30 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/07 00:07:00 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "ray.h"
#include "vector.h"

static void	deactivate_vector_cheker(t_vector *obj, t_object type)
{
	t_hit	hit;
	size_t	i;

	hit.is_hit = true;
	hit.type = type;
	i = 0;
	while (i < obj->size)
	{
		hit.object = vector_get(obj, i);
		checkerboard_on_off(&hit, MOUSE_RIGHT);
		++i;
	}
}

void	deactivate_checkerboard(t_scene *scene)
{
	deactivate_vector_cheker(&scene->cones, CONE);
	deactivate_vector_cheker(&scene->planes, PLANE);
	deactivate_vector_cheker(&scene->spheres, SPHERE);
	deactivate_vector_cheker(&scene->cylinders, CYLINDER);
}
