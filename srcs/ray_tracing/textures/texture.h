/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:00:11 by noavetis          #+#    #+#             */
/*   Updated: 2026/02/06 22:57:32 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "minirt.h"
# include "intersection.h"

# define BUMP_STRENGTH 2.0

typedef void	(*t_checkerboard_fn)(void *, bool);
typedef int		(*t_checker_func)(const t_hit *);

typedef struct s_uv
{
	double	u;
	double	v;
}	t_uv;

bool		load_texture(void *mlx, const char *path, t_loaded_tex *tex);
void		free_texture(void *mlx, t_loaded_tex *tex);
int			get_texture_pixel(t_loaded_tex *tex, int x, int y);

t_uv		get_uv_sphere(const t_hit *hit, const t_sphere *sp);
t_uv		get_uv_plane(const t_hit *hit, const t_plane *pl);
t_uv		get_uv_cylinder(const t_hit *hit, const t_cylinder *cy);
t_uv		get_uv_cone(const t_hit *hit, const t_cone *co);

t_vec3		bump_map(const t_hit *hit, t_loaded_tex *bump, t_uv uv);
t_vec3		get_normal(const t_hit *hit, const t_scene *scene);
t_rgb		get_tex_color(const t_hit *hit, const t_scene *scene);
void		load_scene(t_scene *scene);

#endif
