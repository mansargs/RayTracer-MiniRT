/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:36:16 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 15:27:19 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "phong.h"
#include "intersection.h"

t_rgb	diffuse_color(const t_light *light, const t_hit *hit)
{
	t_vec3	to_light;
	double	distance;
	t_vec3	L;
	double	cos_theta;
	t_rgb	diffuse;
	t_rgb	surface_color;

	to_light = vec_sub(light->position, hit->point);
	distance = vec_magnitude(to_light);
	if (distance < EPS)
		return ((t_rgb){0.0, 0.0, 0.0});
	L = vec_normalize(to_light);
	cos_theta = vec_dot(hit->normal, L);
	if (cos_theta <= 0.0)
		return ((t_rgb){0.0, 0.0,0.0});
	surface_color = find_surface_color(hit);
	diffuse.r = (light->color.r / 255.0) * (surface_color.r / 255.0) * cos_theta * 255.0
		/ (1.0 + distance * 0.1);
	diffuse.g = (light->color.g / 255.0) * (surface_color.g / 255.0) * cos_theta * 255.0
		/ (1.0 + distance * 0.1);
	diffuse.b = (light->color.b / 255.0) * (surface_color.b / 255.0) * cos_theta * 255.0
		/ (1.0 + distance * 0.1);
	return (diffuse);
}
