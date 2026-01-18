/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:36:16 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 01:56:04 by mansargs         ###   ########.fr       */
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

	to_light = vec_sub(light->position, hit->point);
	distance = vec_magnitude(to_light);
	if (distance < EPS)
		return ((t_rgb){0.0, 0.0, 0.0});
	L = vec_normalize(to_light);
	cos_theta = vec_dot(hit->normal, L);
	if (cos_theta <= 0.0)
		return ((t_rgb){0.0, 0.0,0.0});
	diffuse.r = light->color.r * find_surface_color(hit).r * cos_theta
		/ (distance * distance);
	diffuse.g = light->color.g * find_surface_color(hit).g * cos_theta
		/ (distance * distance);
	diffuse.b = light->color.b * find_surface_color(hit).b * cos_theta
		/ (distance * distance);
	return (diffuse);
}
