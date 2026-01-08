#ifndef WINDOW_H
# define WINDOW_H

#include "mlx.h"

# define MLX_FAILED   -1
# define MLX_SUCCESS   0
# define WINDOW_HEIGHT 700
# define WINDOW_WIDTH  900
# define IMAGE_HEIGHT  700
# define IMAGE_WIDTH   900
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
	void		*mlx;
	void		*mlx_window;
	t_data		image;
}				t_window;

#endif
