/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 01:23:42 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/06 02:32:12 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "phong.h"
#include "vector.h"
#include "intersection.h"
#include "ray.h"

static t_rgb	add_colors(t_rgb color1, t_rgb color2)
{
	t_rgb	result;

	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	return (result);
}

int	rgb_to_int(int r, int g, int b)
{
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

static t_rgb	compute_lighting(const t_hit *hit, const t_scene *scene)
{
	size_t			i;
	const t_light	*light;
	t_rgb			diffuse;
	t_rgb			specular;
	t_rgb			result;

	result = (t_rgb){0, 0, 0};
	i = 0;
	while (i < scene->lights.size)
	{
		light = vector_get(&scene->lights, i);
		if (!is_in_shadow(hit->point, light->position, scene))
		{
			diffuse = diffuse_color(light, hit);
			specular = compute_specular(light, scene->chosen_cam, hit);
			result = add_colors(result, add_colors(diffuse, specular));
		}
		++i;
	}
	return (result);
}

static void	apply_checkerboard_if_needed(t_rgb *color, const t_hit *hit)
{
	int	checker;

	if (!hit || !hit->object)
		return ;
	if (hit->type == SPHERE && !((t_sphere *)hit->object)->checkerboard)
		return ;
	if (hit->type == PLANE && !((t_plane *)hit->object)->checkerboard)
		return ;
	if (hit->type == CYLINDER && !((t_cylinder *)hit->object)->checkerboard)
		return ;
	if (hit->type == CONE && !((t_cone *)hit->object)->checkerboard)
		return ;
	checker = get_checker_pattern(hit);
	if (checker)
	{
		color->r *= 0.3;
		color->g *= 0.3;
		color->b *= 0.3;
	}
}

t_rgb	compute_final_color(const t_hit *hit, const t_scene *scene)
{
	t_rgb	final;

	final = compute_ambient(hit, &scene->ambient);
	final = add_colors(final, compute_lighting(hit, scene));
	apply_checkerboard_if_needed(&final, hit);
	return (final);
}
