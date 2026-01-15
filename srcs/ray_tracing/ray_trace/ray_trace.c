/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:27:36 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/15 16:46:30 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

void	ray_trace(const t_ray *ray, t_scene *scene, t_window *win)
{
	t_hit	nearest;
	t_rgb	final_color;

	nearest = objects_intersection(ray, scene);
	if (!nearest.is_hit)
		final_color = (t_rgb){10.0, 10.0, 30.0};
}
