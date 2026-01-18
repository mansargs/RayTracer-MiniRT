/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:40:39 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 01:18:29 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vec_math.h"
#include <math.h>
#include <stdio.h>

void	camera_init_basis(t_camera *cam, int width, int height)
{
	t_vec3	world_up;

	cam->forward = vec_normalize(cam->orientation);
	world_up = (t_vec3){0.0, 1.0, 0.0};
	if (vec_dot(cam->forward, world_up) > 0.999)
		world_up = (t_vec3){1.0, 0.0, 0.0};
	cam->right = vec_normalize(vec_cross(cam->forward, world_up));
	cam->up = vec_normalize(vec_cross(cam->right, cam->forward));
	cam->aspect_ratio = (double)width / (double)height;
	cam->half_height = tan(cam->fov * 0.5 * M_PI / 180.0);
	cam->half_width = cam->aspect_ratio * cam->half_height;
}

void	generate_rays(t_scene *scene, t_window *win)
{
	t_ray			ray;
	t_vec3			dir;
	t_camera_pixel	cp;
	int				x;
	int				y;

	camera_init_basis(&scene->camera, win->width, win->height);
	ray.origin = scene->camera.position;
	y = -1;
	while (++y < win->height)
	{
		x = -1;
		while (++x < win->width)
		{
			cp.px = (2.0 * (x + 0.5) / win->width - 1.0)
				* scene->camera.half_width;
			cp.py = (1.0 - 2.0 * (y + 0.5) / win->height)
				* scene->camera.half_height;
			dir = vec_add(scene->camera.forward,
					vec_add(vec_scale(scene->camera.right, cp.px),
						vec_scale(scene->camera.up, cp.py)));
			ray.direction = vec_normalize(dir);
			ray_trace(&ray, scene, win, x, y);
		}
	}
}

t_vec3	ray_at(const t_ray *ray, double t)
{
	return (vec_add(ray->origin, vec_scale(ray->direction, t)));
}
