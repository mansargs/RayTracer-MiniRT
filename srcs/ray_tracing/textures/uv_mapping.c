/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:42:58 by noavetis          #+#    #+#             */
/*   Updated: 2026/02/06 02:08:35 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "vec_math.h"
#include <math.h>

t_uv	get_uv_sphere(const t_hit *hit, const t_sphere *sp)
{
	t_uv	uv;
	t_vec3	d;

	d = vec_normalize(vec_sub(hit->point, sp->center));
	uv.u = 0.5 + atan2(d.z, d.x) / (2.0 * M_PI);
	uv.v = 0.5 - asin(d.y) / M_PI;
	return (uv);
}

t_uv	get_uv_plane(const t_hit *hit, const t_plane *pl)
{
	t_uv	uv;
	t_vec3	local;
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	world_up;

	local = vec_sub(hit->point, pl->position);
	world_up = (t_vec3){0.0, 1.0, 0.0};
	if (fabs(vec_dot(pl->orientation, world_up)) > 0.999)
		world_up = (t_vec3){1.0, 0.0, 0.0};
	u_axis = vec_normalize(vec_cross(world_up, pl->orientation));
	v_axis = vec_normalize(vec_cross(pl->orientation, u_axis));
	uv.u = fmod(vec_dot(local, u_axis) * 0.1, 1.0);
	uv.v = fmod(vec_dot(local, v_axis) * 0.1, 1.0);
	if (uv.u < 0)
		uv.u += 1.0;
	if (uv.v < 0)
		uv.v += 1.0;
	return (uv);
}

t_uv	get_uv_cylinder(const t_hit *hit, const t_cylinder *cy)
{
	t_uv	uv;
	t_vec3	axis;
	t_vec3	to_point;
	t_vec3	radial;
	double	theta;

	axis = vec_normalize(cy->orientation);
	to_point = vec_sub(hit->point, cy->center);
	uv.v = (vec_dot(to_point, axis) / cy->height) + 0.5;
	radial = vec_sub(to_point, vec_scale(axis, vec_dot(to_point, axis)));
	radial = vec_normalize(radial);
	theta = atan2(radial.z, radial.x);
	uv.u = (theta + M_PI) / (2.0 * M_PI);
	return (uv);
}

t_uv	get_uv_cone(const t_hit *hit, const t_cone *co)
{
	t_uv	uv;
	t_vec3	axis;
	t_vec3	to_point;
	t_vec3	radial;
	double	h;

	axis = vec_normalize(co->orientation);
	to_point = vec_sub(hit->point, co->center);
	h = vec_dot(to_point, axis);
	uv.v = h / co->height;
	if (uv.v < 0.0)
		uv.v = 0.0;
	if (uv.v > 1.0)
		uv.v = 1.0;
	radial = vec_sub(to_point, vec_scale(axis, h));
	if (vec_magnitude(radial) > EPS)
		radial = vec_normalize(radial);
	uv.u = (atan2(radial.z, radial.x) + M_PI) / (2.0 * M_PI);
	return (uv);
}
