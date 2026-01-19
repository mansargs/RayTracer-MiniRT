/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 01:23:42 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 19:37:10 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "phong.h"
#include "vector.h"

static t_rgb	add_colors(t_rgb color1, t_rgb color2)
{
	t_rgb	result;

	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	return (result);
}

t_rgb	compute_final_color(const t_hit *hit, const t_scene *scene)
{
	t_rgb			final;
	const t_light	*light;
	t_rgb			diffuse;
	t_rgb			specular;
	size_t			i;

	final = compute_ambient(hit, &scene->ambient);
	i = 0;
	while (i < scene->lights.size)
	{
		light = vector_get(&scene->lights, i);
		if (!is_in_shadow(hit->point, light->position, scene))
		{
			diffuse = diffuse_color(light, hit);
			specular = compute_specular(light, &scene->camera, hit);
			final = add_colors(final, add_colors(diffuse, specular));
		}
		++i;
	}
	return (final);
}
