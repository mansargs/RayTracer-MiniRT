/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:40:39 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/27 00:25:48 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vec_math.h"
#include "intersection.h"
#include <math.h>
#include <stdio.h>
#include <pthread.h>

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

static void	*thread_render(void *arg)
{
	t_thread_data	*data;
	t_iter			iter;

	data = (t_thread_data *)arg;
	iter.y = data->start_y;
	while (iter.y < data->end_y)
	{
		iter.x = 0;
		while (iter.x < data->win->width)
		{
			trace_pixel(data->scene, data->win, iter);
			iter.x++;
		}
		iter.y++;
	}
	return (NULL);
}

void	generate_rays(t_scene *scene, t_window *win)
{
	pthread_t		threads[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	int				rows_per_thread;
	int				i;

	scene->chosen_cam = chose_camera(scene);
	camera_init_basis(scene->chosen_cam, win->width, win->height);
	rows_per_thread = win->height / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		thread_data[i].scene = scene;
		thread_data[i].win = win;
		thread_data[i].start_y = i * rows_per_thread;
		if (i == NUM_THREADS - 1)
			thread_data[i].end_y = win->height;
		else
			thread_data[i].end_y = (i + 1) * rows_per_thread;
		pthread_create(&threads[i], NULL, thread_render, &thread_data[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
