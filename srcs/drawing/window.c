/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:23:01 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/15 16:04:24 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

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
