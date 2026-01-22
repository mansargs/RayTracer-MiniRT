/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:24:01 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/22 13:24:11 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

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

void	start_loop(t_window *win)
{
	mlx_hook(win->mlx_window, 2, 1L << 0, handle_keypress, win);
	mlx_hook(win->mlx_window, X_EVENT_DESTROY, 0, handle_destroy, win);
	mlx_loop(win->mlx);
}
