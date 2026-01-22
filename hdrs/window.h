/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:47:50 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/22 13:24:34 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "mlx.h"

# define MLX_FAILED   -1
# define MLX_SUCCESS   0
# define WINDOW_NAME   "RayTracer-MiniRT"
# define KEY_ESC 65307
# define X_EVENT_DESTROY 17

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
void	render_image(t_window *win);
void	start_loop(t_window *win);

#endif
