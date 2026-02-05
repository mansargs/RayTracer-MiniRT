/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:42:03 by noavetis          #+#    #+#             */
/*   Updated: 2026/02/06 02:20:31 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "vector.h"
#include <stddef.h>

static void	load_material_textures(void *mlx, t_material *mat)
{
	if (mat->texture_path)
		load_texture(mlx, mat->texture_path, &mat->color_tex);
	if (mat->bump_map_path)
		load_texture(mlx, mat->bump_map_path, &mat->bump_tex);
}

static void	load_materials_from_vector(void *mlx, t_vector *vec,
		size_t mat_offset)
{
	size_t		i;
	void		*obj;
	t_material	*mat;

	i = 0;
	while (i < vec->size)
	{
		obj = vector_get(vec, i++);
		mat = (t_material *)((char *)obj + mat_offset);
		load_material_textures(mlx, mat);
	}
}

void	load_scene(void *mlx, t_scene *scene)
{
	load_materials_from_vector(mlx, &scene->spheres,
		offsetof(t_sphere, mat));
	load_materials_from_vector(mlx, &scene->planes,
		offsetof(t_plane, mat));
	load_materials_from_vector(mlx, &scene->cylinders,
		offsetof(t_cylinder, mat));
	load_materials_from_vector(mlx, &scene->cones,
		offsetof(t_cone, mat));
}
