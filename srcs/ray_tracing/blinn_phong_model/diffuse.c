/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:36:16 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/06 23:01:03 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "phong.h"
#include "intersection.h"
#include "texture.h"

t_rgb	diffuse_color(const t_light *light, const t_hit *hit,
	const t_scene *scene)
{
	t_vec3	to_light;
	double	distance;
	double	cos_theta;
	t_rgb	diffuse;
	t_vec3	normal;

	to_light = vec_sub(light->position, hit->point);
	distance = vec_magnitude(to_light);
	if (distance < EPS)
		return ((t_rgb){0, 0, 0});
	to_light = vec_scale(to_light, 1.0 / distance);
	normal = get_normal(hit, scene);
	cos_theta = vec_dot(normal, to_light);
	if (cos_theta <= 0.0)
		return ((t_rgb){0, 0, 0});
	diffuse = find_surface_color(hit, scene);
	diffuse.r = (light->color.r * diffuse.r / 255.0)
		* cos_theta / (1.0 + distance * 0.1);
	diffuse.g = (light->color.g * diffuse.g / 255.0)
		* cos_theta / (1.0 + distance * 0.1);
	diffuse.b = (light->color.b * diffuse.b / 255.0)
		* cos_theta / (1.0 + distance * 0.1);
	return (diffuse);
}
