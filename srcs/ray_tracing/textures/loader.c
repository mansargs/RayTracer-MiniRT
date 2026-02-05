/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:37:59 by noavetis          #+#    #+#             */
/*   Updated: 2026/02/06 02:06:14 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "vec_math.h"
#include "libft.h"
#include <math.h>
#include <unistd.h>

bool	load_texture(void *mlx, const char *path, t_loaded_tex *tex)
{
	if (!path || !mlx)
		return (false);
	tex->img = mlx_xpm_file_to_image(mlx, (char *)path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		ft_putendl_fd("Warning: Failed to load texture",
			STDERR_FILENO);
		tex->loaded = false;
		return (false);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	tex->loaded = true;
	return (true);
}

void	free_texture(void *mlx, t_loaded_tex *tex)
{
	if (tex->loaded && tex->img)
		mlx_destroy_image(mlx, tex->img);
	tex->loaded = false;
	tex->img = NULL;
}

int	get_texture_pixel(t_loaded_tex *tex, int x, int y)
{
	char	*pixel;

	if (!tex->loaded || !tex->addr)
		return (0);
	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}
