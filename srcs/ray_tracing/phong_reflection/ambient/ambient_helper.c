/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:31:42 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/14 16:23:44 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "intersection.h"
#include "ambient.h"

static t_rgb	sphere_color(void *obj)
{
	return (((t_sphere *)obj)->color);
}

static t_rgb	plane_color(void *obj)
{
	return (((t_plane *)obj)->color);
}

static t_rgb	cyl_color(void *obj)
{
	return (((t_cylinder *)obj)->color);
}

static t_rgb	cone_color(void *obj)
{
	return (((t_cone *)obj)->color);
}

t_rgb	find_surface_color(const t_hit *hit)
{
	static const t_get_color_fn	table[] = {
	[SPHERE] = sphere_color,
	[PLANE] = plane_color,
	[CYLINDER] = cyl_color,
	[CONE] = cone_color,
	};

	if (!hit || !hit->is_hit || !hit->object)
		return ((t_rgb){0.0, 0.0, 0.0});
	if (hit->type >= 1 && hit->type < (int)(sizeof(table) / sizeof(table[0])))
		if (table[hit->type])
			return (table[hit->type](hit->object));
	return ((t_rgb){0.0, 0.0, 0.0});
}
