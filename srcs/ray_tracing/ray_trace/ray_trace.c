/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:27:36 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 15:26:03 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "phong.h"
#include "window.h"

// static int	get_object_color(t_hit *hit)
// {
// 	t_sphere	*sphere;
// 	t_plane		*plane;
// 	t_rgb		final_color;

// 	final_color = compute_final_color(hit, scene)
// 	if (hit->type == SPHERE)
// 	{
// 		sphere = (t_sphere *)hit->object;
// 		return (rgb_to_int((int)sphere->color.r, (int)sphere->color.g,
// 				(int)sphere->color.b));
// 	}
// 	else if (hit->type == PLANE)
// 	{
// 		plane = (t_plane *)hit->object;
// 		return (rgb_to_int((int)plane->color.r, (int)plane->color.g,
// 				(int)plane->color.b));
// 	}
// 	return (rgb_to_int(100, 100, 100));
// }

#include <stdio.h>

void	ray_trace(const t_ray *ray, t_scene *scene, t_window *win, int x, int y)
{
	t_hit	nearest;
	int		color;
	t_rgb	final;

	nearest = objects_intersection(ray, scene);
	if (!nearest.is_hit)
		color = rgb_to_int(10, 10, 30);
	else
	{
		final = compute_final_color(&nearest, scene);
		color = rgb_to_int((int)final.r, (int)final.g, (int)final.b);
	}
	put_pixel(win, x, y, color);
}
