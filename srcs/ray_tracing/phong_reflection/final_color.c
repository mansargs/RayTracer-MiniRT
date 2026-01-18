/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 01:23:42 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 01:56:12 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "phong.h"
#include "vector.h"

t_rgb	compute_final_color(const t_hit *hit, const t_scene *scene)
{
	t_rgb			final;
	const t_light	*light;
	t_rgb			diffuse;
	size_t			i;

	final = compute_ambient(hit, &scene->ambient);
	i = 0;
	while (i < scene->lights.size)
	{
		light = vector_get(&scene->lights, i);
		if (!is_in_shadow(hit->point, light->position, scene))
		{
			diffuse = diffuse_color(light, hit);
			final.r += diffuse.r;
			final.g += diffuse.g;
			final.b += diffuse.b;
		}
		++i;
	}
	return (final);
}
