/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:27:36 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/06 02:44:25 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "intersection.h"
#include "phong.h"
#include "vector.h"
#include "window.h"

static t_vec3	compute_ray_dir(
	t_camera *cam,
	t_camera_pixel *cp)
{
	t_vec3	dir;

	dir = vec_add(cam->forward,
			vec_add(
				vec_scale(cam->right, cp->px),
				vec_scale(cam->up, cp->py)));
	return (vec_normalize(dir));
}

t_hit	trace_pixel(t_scene *scene, t_window *win, t_iter iter)
{
	t_ray			ray;
	t_camera_pixel	cp;

	cp.px = (2.0 * (iter.x + 0.5) / win->width - 1.0)
		* scene->chosen_cam->half_width;
	cp.py = (1.0 - 2.0 * (iter.y + 0.5) / win->height)
		* scene->chosen_cam->half_height;
	ray.origin = scene->chosen_cam->position;
	ray.direction = compute_ray_dir(scene->chosen_cam, &cp);
	return (ray_trace(&ray, scene, win, iter));
}

t_camera	*chose_camera(t_scene *scene)
{
	return ((t_camera *)vector_get(&scene->camera, scene->state.camera_idx));
}

t_vec3	ray_at(const t_ray *ray, double t)
{
	return (vec_add(ray->origin, vec_scale(ray->direction, t)));
}

t_hit	ray_trace(const t_ray *ray, t_scene *scene, t_window *win, t_iter pos)
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
	return (nearest);
}
