/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:27:36 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/22 14:45:23 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "phong.h"
#include "vector.h"
#include "window.h"

t_camera	*chose_camera(t_scene *scene)
{
	return ((t_camera *)vector_get(&scene->camera, scene->state.camera_idx));
}

void	ray_trace(const t_ray *ray, t_scene *scene, t_window *win, t_iter pos)
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
	put_pixel(win, pos.x, pos.y, color);
}
