/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:43:06 by noavetis          #+#    #+#             */
/*   Updated: 2026/01/27 15:09:14 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "vec_math.h"
#include <math.h>

static double	color_to_height(int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	return ((r * 0.299 + g * 0.587 + b * 0.114) / 255.0);
}

static t_vec3	get_tangent(t_vec3 normal)
{
	t_vec3	up;

	up = (t_vec3){0.0, 1.0, 0.0};
	if (fabs(vec_dot(normal, up)) > 0.999)
		up = (t_vec3){1.0, 0.0, 0.0};
	return (vec_normalize(vec_cross(up, normal)));
}

static void	gradient(t_loaded_tex *bump, t_uv uv, double *dx, double *dy)
{
	int		x;
	int		y;
	double	h_l;
	double	h_r;
	double	h_u;
	double	h_d;

	x = (int)(uv.u * bump->width);
	y = (int)(uv.v * bump->height);
	h_l = color_to_height(get_texture_pixel(bump, x - 1, y));
	h_r = color_to_height(get_texture_pixel(bump, x + 1, y));
	h_u = color_to_height(get_texture_pixel(bump, x, y - 1));
	h_d = color_to_height(get_texture_pixel(bump, x, y + 1));
	*dx = (h_r - h_l) * BUMP_STRENGTH;
	*dy = (h_d - h_u) * BUMP_STRENGTH;
}

t_vec3	bump_map(const t_hit *hit, t_loaded_tex *bump, t_uv uv)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	perturbed;
	double	dx;
	double	dy;

	if (!bump->loaded)
		return (hit->normal);
	gradient(bump, uv, &dx, &dy);
	tangent = get_tangent(hit->normal);
	bitangent = vec_cross(hit->normal, tangent);
	perturbed = vec_add(hit->normal,
			vec_add(vec_scale(tangent, -dx), vec_scale(bitangent, -dy)));
	return (vec_normalize(perturbed));
}
