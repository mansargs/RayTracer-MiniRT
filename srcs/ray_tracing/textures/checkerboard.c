/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 00:16:30 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/06 03:02:31 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "texture.h"
#include <math.h>

static int	get_plane_checker(const t_hit *hit)
{
	t_uv	uv;

	uv = get_uv_plane(hit, (t_plane *)hit->object);
	uv.u = floor(uv.u * CHECKERBOARD_SCALE);
	uv.v = floor(uv.v * CHECKERBOARD_SCALE);
	return (((int)uv.u + (int)uv.v) & 1);
}

static int	get_sphere_checker(const t_hit *hit)
{
	t_uv	uv;

	uv = get_uv_sphere(hit, (t_sphere *)hit->object);
	uv.u = floor(uv.u * CHECKERBOARD_SCALE * 2.2);
	uv.v = floor(uv.v * CHECKERBOARD_SCALE * 1.5);
	return (((int)uv.u + (int)uv.v) & 1);
}

static int	get_cone_checker(const t_hit *hit)
{
	t_uv	uv;

	uv = get_uv_cone(hit, (t_cone *)hit->object);
	uv.u = floor(uv.u * CHECKERBOARD_SCALE * 2.2);
	uv.v = floor(uv.v * CHECKERBOARD_SCALE * 1.5);
	return (((int)uv.u + (int)uv.v) & 1);
}

static int	get_cylinder_checker(const t_hit *hit)
{
	t_uv	uv;

	uv = get_uv_cylinder(hit, (t_cylinder *)hit->object);
	uv.u = floor(uv.u * CHECKERBOARD_SCALE * 3.0);
	uv.v = floor(uv.v * CHECKERBOARD_SCALE * 0.5);
	return (((int)uv.u + (int)uv.v) & 1);
}

int	get_checker_pattern(const t_hit *hit)
{
	static const t_checker_func	g_checker_funcs[] = {
	[PLANE] = get_plane_checker,
	[SPHERE] = get_sphere_checker,
	[CYLINDER] = get_cylinder_checker,
	[CONE] = get_cone_checker,
	};

	if (!hit || !hit->is_hit || !hit->object)
		return (0);
	return (g_checker_funcs[hit->type](hit));
}
