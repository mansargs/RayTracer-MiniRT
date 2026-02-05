/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:40:39 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/06 02:44:11 by mansargs         ###   ########.fr       */
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

static void	join_render_threads(pthread_t *threads)
{
	int	i;

	if (!threads)
		return ;
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		++i;
	}
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
	join_render_threads(threads);
}
