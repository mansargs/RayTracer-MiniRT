/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:43:01 by noavetis          #+#    #+#             */
/*   Updated: 2026/02/06 23:01:01 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

static t_uv	get_uv_for_hit(const t_hit *hit)
{
	t_uv	uv;

	uv.u = 0;
	uv.v = 0;
	if (hit->type == SPHERE)
		uv = get_uv_sphere(hit, (t_sphere *)hit->object);
	else if (hit->type == PLANE)
		uv = get_uv_plane(hit, (t_plane *)hit->object);
	else if (hit->type == CYLINDER)
		uv = get_uv_cylinder(hit, (t_cylinder *)hit->object);
	else if (hit->type == CONE)
		uv = get_uv_cone(hit, (t_cone *)hit->object);
	return (uv);
}

static t_loaded_tex	*get_bump_tex(const t_hit *hit)
{
	if (hit->type == SPHERE)
		return (&((t_sphere *)hit->object)->mat.bump_tex);
	else if (hit->type == PLANE)
		return (&((t_plane *)hit->object)->mat.bump_tex);
	else if (hit->type == CYLINDER)
		return (&((t_cylinder *)hit->object)->mat.bump_tex);
	else if (hit->type == CONE)
		return (&((t_cone *)hit->object)->mat.bump_tex);
	return (NULL);
}

t_vec3	get_normal(const t_hit *hit, const t_scene *scene)
{
	t_loaded_tex	*bump;
	t_uv			uv;

	bump = get_bump_tex(hit);
	if (!scene || !scene->state.bump_on)
		return (hit->normal);
	if (!bump || !bump->loaded)
		return (hit->normal);
	uv = get_uv_for_hit(hit);
	return (bump_map(hit, bump, uv));
}
