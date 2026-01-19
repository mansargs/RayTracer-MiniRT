/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:27:36 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 17:26:26 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "phong.h"
#include "window.h"

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
