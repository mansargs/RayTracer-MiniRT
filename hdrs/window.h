#ifndef WINDOW_H
# define WINDOW_H

#include "mlx.h"

# define MLX_FAILED   -1
# define MLX_SUCCESS   0
# define WINDOW_NAME   "RayTracer-MiniRT"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct	s_window
{
	void	*mlx;
	void	*mlx_window;
	t_data	image;
	int		width;
	int		height;
}			t_window;

void	cleanup_window(t_window* win);
int		init_window_params(t_window* win);

#endif
