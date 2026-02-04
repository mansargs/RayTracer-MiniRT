/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 00:16:30 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/04 21:06:01 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include <math.h>

static int	spherical_checker(const t_vec3 n)
{
	double	u;
	double	v;
	int		iu;
	int		iv;

	u = 0.5 + atan2(n.z, n.x) / (2.0 * M_PI);
	v = 0.5 - asin(n.y) / M_PI;
	iu = (int)floor(u * CHECKERBOARD_SCALE * 2.2);
	iv = (int)floor(v * CHECKERBOARD_SCALE * 1.5);
	return ((iu + iv) & 1);
}

static int	get_plane_checker(const t_hit *hit)
{
	int	u;
	int	v;

	u = (int)floor(hit->point.x * CHECKERBOARD_SCALE);
	v = (int)floor(hit->point.z * CHECKERBOARD_SCALE);
	return ((u + v) & 1);
}

static int	get_sphere_checker(const t_hit *hit)
{
	t_sphere	*sphere;
	t_vec3		to_point;
	t_vec3		normal;

	sphere = (t_sphere *)hit->object;
	to_point = vec_sub(hit->point, sphere->center);
	normal = vec_normalize(to_point);
	return (spherical_checker(normal));
}

static int	get_cone_checker(const t_hit *hit)
{
	t_cone	*cone;
	t_vec3	to_point;
	t_vec3	normal;

	cone = (t_cone *)hit->object;
	to_point = vec_sub(hit->point, cone->center);
	normal = vec_normalize(to_point);
	return (spherical_checker(normal));
}

static int	get_cylinder_checker(const t_hit *hit)
{
	t_cylinder	*cyl;
	t_vec3		radial;
	double		u;
	double		v;
	int			iu_iv;

	cyl = (t_cylinder *)hit->object;
	v = vec_dot(vec_sub(hit->point, cyl->center),
		vec_normalize(cyl->orientation));
	radial = vec_sub(vec_sub(hit->point, cyl->center),
		vec_scale(vec_normalize(cyl->orientation), v));
	if (vec_magnitude(radial) < 1e-6)
		return (0);
	radial = vec_scale(radial, 1.0 / vec_magnitude(radial));
	u = (atan2(radial.z, radial.x) + M_PI) / (2.0 * M_PI);
	iu_iv = (int)floor(u * CHECKERBOARD_SCALE * 3.0)
		+ (int)floor(v * CHECKERBOARD_SCALE * 0.5);
	return (iu_iv & 1);
}

typedef int	(*t_checker_func)(const t_hit *);

int	get_checker_pattern(const t_hit *hit)
{
	static const t_checker_func	g_checker_funcs[] = {
	[PLANE]    = get_plane_checker,
	[SPHERE]   = get_sphere_checker,
	[CYLINDER] = get_cylinder_checker,
	[CONE]     = get_cone_checker,
	};

	if (!hit || !hit->is_hit || !hit->object)
		return (0);
	return (g_checker_funcs[hit->type](hit));
}
