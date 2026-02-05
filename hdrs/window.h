/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:47:50 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/06 03:15:14 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "mlx.h"
# include "minirt.h"

# define MLX_FAILED   -1
# define MLX_SUCCESS   0
# define WINDOW_NAME   "RayTracer-MiniRT"
# define KEY_ESC 65307
# define X_EVENT_DESTROY 17
# define KEY_SPACE 32
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define MOUSE_LEFT   1
# define MOUSE_RIGHT  3
# define CHECKERBOARD_SCALE 10
# define MOVE_SPEED 0.6
# define ROT_SPEED 0.05
# define BUMP_STRENGHT 10.0

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
	t_scene	*scene;
}			t_window;

void		cleanup_window(t_window *win);
int			init_window_params(t_window *win, t_scene *scene);
void		put_pixel(t_window *win, int x, int y, int color);
void		render_image(t_window *win);
int			render_loop(t_window *win);
void		rotate_camera(t_camera *cam, int keycode);
void		start_loop(t_window *win);
t_camera	*chose_camera(t_scene *scene);

#endif
