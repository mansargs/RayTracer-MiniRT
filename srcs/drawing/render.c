/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 03:08:27 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/06 03:08:28 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "ray.h"
#include "intersection.h"
#include <math.h>

void	put_pixel(t_window *win, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= win->width || y < 0 || y >= win->height)
		return ;
	dst = win->image.addr + (y * win->image.line_length
			+ x * (win->image.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static t_vec3	rotate_around_axis(t_vec3 v, t_vec3 axis, double angle)
{
	double	c;
	double	s;
	t_vec3	result;

	c = cos(angle);
	s = sin(angle);
	result.x = v.x * (c + axis.x * axis.x * (1 - c))
		+ v.y * (axis.x * axis.y * (1 - c) - axis.z * s)
		+ v.z * (axis.x * axis.z * (1 - c) + axis.y * s);
	result.y = v.x * (axis.y * axis.x * (1 - c) + axis.z * s)
		+ v.y * (c + axis.y * axis.y * (1 - c))
		+ v.z * (axis.y * axis.z * (1 - c) - axis.x * s);
	result.z = v.x * (axis.z * axis.x * (1 - c) - axis.y * s)
		+ v.y * (axis.z * axis.y * (1 - c) + axis.x * s)
		+ v.z * (c + axis.z * axis.z * (1 - c));
	return (result);
}

void	rotate_camera(t_camera *cam, int keycode)
{
	t_vec3	world_up;

	world_up = (t_vec3){0.0, 1.0, 0.0};
	if (keycode == KEY_LEFT)
		cam->orientation = rotate_around_axis(cam->orientation,
				world_up, ROT_SPEED);
	else if (keycode == KEY_RIGHT)
		cam->orientation = rotate_around_axis(cam->orientation,
				world_up, -ROT_SPEED);
	else if (keycode == KEY_UP)
		cam->orientation = rotate_around_axis(cam->orientation,
				cam->right, ROT_SPEED);
	else if (keycode == KEY_DOWN)
		cam->orientation = rotate_around_axis(cam->orientation,
				cam->right, -ROT_SPEED);
	cam->orientation = vec_normalize(cam->orientation);
}

void	render_image(t_window *win)
{
	mlx_put_image_to_window(win->mlx, win->mlx_window, win->image.img, 0, 0);
}

int	render_loop(t_window *win)
{
	generate_rays(win->scene, win);
	render_image(win);
	return (0);
}
