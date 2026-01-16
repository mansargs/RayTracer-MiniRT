/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:23:01 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/16 23:12:39 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

#define KEY_ESC 65307
#define X_EVENT_DESTROY 17

void	put_pixel(t_window *win, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= win->width || y < 0 || y >= win->height)
		return ;
	dst = win->image.addr + (y * win->image.line_length
			+ x * (win->image.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	rgb_to_int(int r, int g, int b)
{
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

static int	handle_keypress(int keycode, t_window *win)
{
	if (keycode == KEY_ESC)
	{
		mlx_loop_end(win->mlx);
	}
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

int	init_window_params(t_window *win)
{
	win->width = 800;
	win->height = 600;
	win->mlx = mlx_init();
	if (!win->mlx)
		return (ft_putendl_fd("MLX init failed", STDERR_FILENO), MLX_FAILED);
	win->mlx_window = mlx_new_window(win->mlx, win->width,
			win->height, WINDOW_NAME);
	if (!win->mlx_window)
		return (ft_putendl_fd("Window opening failed", STDERR_FILENO),
			MLX_FAILED);
	win->image.img = mlx_new_image(win->mlx, win->width, win->height);
	if (!win->image.img)
		return (ft_putendl_fd("Image creating failed", STDERR_FILENO),
			MLX_FAILED);
	win->image.addr = mlx_get_data_addr(win->image.img,
			&win->image.bits_per_pixel, &win->image.line_length,
			&win->image.endian);
	return (MLX_SUCCESS);
}

void	cleanup_window(t_window *win)
{
	mlx_destroy_image(win->mlx, win->image.img);
	mlx_destroy_window(win->mlx, win->mlx_window);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
}
