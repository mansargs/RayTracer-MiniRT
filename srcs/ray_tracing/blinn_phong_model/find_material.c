/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:57:36 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 19:27:49 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:31:42 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 01:46:33 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "intersection.h"
#include "phong.h"

static const t_material	*sphere_mat(void *obj)
{
	return (&((t_sphere *)obj)->mat);
}

static const t_material	*plane_mat(void *obj)
{
	return (&((t_plane *)obj)->mat);
}

static const t_material	*cyl_mat(void *obj)
{
	return (&((t_cylinder *)obj)->mat);
}

static const t_material	*cone_mat(void *obj)
{
	return (&((t_cone *)obj)->mat);
}

const t_material	*find_material(const t_hit *hit)
{
	static const t_get_mat_fn	table[] = {
	[SPHERE] = sphere_mat,
	[PLANE] = plane_mat,
	[CYLINDER] = cyl_mat,
	[CONE] = cone_mat,
	};

	if (!hit || !hit->is_hit || !hit->object)
		return (NULL);
	if (hit->type >= 1 && hit->type < (int)(sizeof(table) / sizeof(table[0])))
		if (table[hit->type])
			return (table[hit->type](hit->object));
	return (NULL);
}
