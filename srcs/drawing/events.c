/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 03:08:38 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/06 03:10:22 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "vec_math.h"
#include "intersection.h"
#include "ray.h"

static int	handle_keypress(int keycode, t_window *win)
{
	t_scene	*scene;

	scene = win->scene;
	if (keycode == KEY_ESC)
		mlx_loop_end(win->mlx);
	else if (keycode == KEY_SPACE)
		scene->state.camera_idx = (scene->state.camera_idx + 1)
			% scene->camera.size;
	else if (keycode == KEY_S)
		scene->chosen_cam->position = vec_sub(scene->chosen_cam->position,
				vec_scale(scene->chosen_cam->forward, MOVE_SPEED));
	else if (keycode == KEY_A)
		scene->chosen_cam->position = vec_sub(scene->chosen_cam->position,
				vec_scale(scene->chosen_cam->right, MOVE_SPEED));
	else if (keycode == KEY_W)
		scene->chosen_cam->position = vec_add(scene->chosen_cam->position,
				vec_scale(scene->chosen_cam->forward, MOVE_SPEED));
	else if (keycode == KEY_D)
		scene->chosen_cam->position = vec_add(scene->chosen_cam->position,
				vec_scale(scene->chosen_cam->right, MOVE_SPEED));
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT
		|| keycode == KEY_UP || keycode == KEY_DOWN)
		rotate_camera(scene->chosen_cam, keycode);
	return (0);
}

static int	handle_destroy(t_window *win)
{
	mlx_loop_end(win->mlx);
	return (0);
}

static int	mouse_handler(int button, int x, int y, void *param)
{
	t_window	*win;
	t_hit		nearest;

	win = (t_window *)param;
	nearest = trace_pixel(win->scene, win, (t_iter){x, y});
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
