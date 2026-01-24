/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:24:01 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/24 16:02:23 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "ray.h"
#include "intersection.h"

void	put_pixel(t_window *win, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= win->width || y < 0 || y >= win->height)
		return ;
	dst = win->image.addr + (y * win->image.line_length
			+ x * (win->image.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static int	handle_keypress(int keycode, t_window *win)
{
	if (keycode == KEY_ESC)
		mlx_loop_end(win->mlx);
	else if (keycode == KEY_SPACE)
		win->scene->state.camera_idx = (win->scene->state.camera_idx + 1)
			% win->scene->camera.size;
	return (0);
}

static int	handle_destroy(t_window *win)
{
	mlx_loop_end(win->mlx);
	return (0);
}

void	render_image(t_window *win)
{
	mlx_put_image_to_window(win->mlx, win->mlx_window, win->image.img, 0, 0);
}

static int	render_loop(t_window *win)
{
	generate_rays(win->scene, win);
	render_image(win);
	return (0);
}

static int	mouse_handler(int button, int x, int y, void *param)
{
	t_window	*win;
	t_hit		nearest;

	win = (t_window *)param;
	nearest = trace_pixel(win->scene, win, (t_iter){.x = x, .y = y});
	if (nearest.is_hit)
		checkerboard_on_off(&nearest, button);
	return (0);
}

void	start_loop(t_window *win)
{
	mlx_hook(win->mlx_window, 2, 1L << 0, handle_keypress, win);
	mlx_hook(win->mlx_window, X_EVENT_DESTROY, 0, handle_destroy, win);
	mlx_loop_hook(win->mlx, render_loop, win);
	mlx_mouse_hook(win->mlx_window, mouse_handler, win);
	mlx_loop(win->mlx);
}
