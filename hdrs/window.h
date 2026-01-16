/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:47:50 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/16 23:12:59 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "mlx.h"

# define MLX_FAILED   -1
# define MLX_SUCCESS   0
# define WINDOW_NAME   "RayTracer-MiniRT"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_window
{
	void	*mlx;
	void	*mlx_window;
	t_data	image;
	int		width;
	int		height;
}			t_window;

void	cleanup_window(t_window *win);
int		init_window_params(t_window *win);
void	put_pixel(t_window *win, int x, int y, int color);
int		rgb_to_int(int r, int g, int b);
void	render_image(t_window *win);
void	start_loop(t_window *win);

#endif
