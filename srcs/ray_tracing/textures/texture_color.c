/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:40:54 by noavetis          #+#    #+#             */
/*   Updated: 2026/02/06 23:01:01 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

static t_uv	get_uv_for_hit(const t_hit *hit)
{
	t_uv	uv;

	uv.u = 0;
	uv.v = 0;
	if (hit->type == SPHERE)
		uv = get_uv_sphere(hit, (t_sphere *)hit->object);
	else if (hit->type == PLANE)
		uv = get_uv_plane(hit, (t_plane *)hit->object);
	else if (hit->type == CYLINDER)
		uv = get_uv_cylinder(hit, (t_cylinder *)hit->object);
	else if (hit->type == CONE)
		uv = get_uv_cone(hit, (t_cone *)hit->object);
	return (uv);
}

static t_loaded_tex	*get_color_tex(const t_hit *hit)
{
	if (hit->type == SPHERE)
		return (&((t_sphere *)hit->object)->mat.color_tex);
	else if (hit->type == PLANE)
		return (&((t_plane *)hit->object)->mat.color_tex);
	else if (hit->type == CYLINDER)
		return (&((t_cylinder *)hit->object)->mat.color_tex);
	else if (hit->type == CONE)
		return (&((t_cone *)hit->object)->mat.color_tex);
	return (NULL);
}

static t_rgb	sample_texture(t_loaded_tex *tex, t_uv uv)
{
	int		x;
	int		y;
	int		color;
	t_rgb	rgb;

	x = (int)(uv.u * tex->width) % tex->width;
	y = (int)(uv.v * tex->height) % tex->height;
	if (x < 0)
		x += tex->width;
	if (y < 0)
		y += tex->height;
	color = get_texture_pixel(tex, x, y);
	rgb.r = (color >> 16) & 0xFF;
	rgb.g = (color >> 8) & 0xFF;
	rgb.b = color & 0xFF;
	return (rgb);
}

t_rgb	get_tex_color(const t_hit *hit, const t_scene *scene)
{
	t_loaded_tex	*tex;
	t_uv			uv;
	t_rgb			none;

	none.r = -1;
	none.g = -1;
	none.b = -1;
	tex = get_color_tex(hit);
	if (!scene || !scene->state.texture_on)
		return (none);
	if (!tex || !tex->loaded)
		return (none);
	uv = get_uv_for_hit(hit);
	return (sample_texture(tex, uv));
}
