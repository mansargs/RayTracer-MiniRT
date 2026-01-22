/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:40:39 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/22 15:47:22 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vec_math.h"
#include <math.h>
#include <stdio.h>

static void	camera_init_basis(t_camera *cam, int width, int height)
{
	t_vec3	world_up;

	cam->forward = vec_normalize(cam->orientation);
	world_up = (t_vec3){0.0, 1.0, 0.0};
	if (fabs(vec_dot(cam->forward, world_up)) > 0.999)
		world_up = (t_vec3){0.0, 0.0, 1.0};
	cam->right = vec_normalize(vec_cross(cam->forward, world_up));
	cam->up = vec_normalize(vec_cross(cam->right, cam->forward));
	cam->aspect_ratio = (double)width / (double)height;
	cam->half_height = tan(cam->fov * 0.5 * M_PI / 180.0);
	cam->half_width = cam->aspect_ratio * cam->half_height;
}

t_vec3	ray_at(const t_ray *ray, double t)
{
	return (vec_add(ray->origin, vec_scale(ray->direction, t)));
}

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

static void	trace_pixel(t_scene *scene, t_window *win, t_iter iter)
{
	t_ray			ray;
	t_camera_pixel	cp;

	cp.px = (2.0 * (iter.x + 0.5) / win->width - 1.0)
		* scene->chosen_cam->half_width;
	cp.py = (1.0 - 2.0 * (iter.y + 0.5) / win->height)
		* scene->chosen_cam->half_height;
	ray.origin = scene->chosen_cam->position;
	ray.direction = compute_ray_dir(scene->chosen_cam, &cp);
	ray_trace(&ray, scene, win, iter);
}

void	generate_rays(t_scene *scene, t_window *win)
{
	t_iter		iter;

	scene->chosen_cam = chose_camera(scene);
	camera_init_basis(scene->chosen_cam, win->width, win->height);
	iter.y = 0;
	while (iter.y < win->height)
	{
		iter.x = 0;
		while (iter.x < win->width)
		{
			trace_pixel(scene, win, iter);
			iter.x++;
		}
		iter.y++;
	}
}
