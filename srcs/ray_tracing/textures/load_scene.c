/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 01:42:03 by noavetis          #+#    #+#             */
/*   Updated: 2026/01/27 15:12:38 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "vector.h"

static void	load_material_textures(void *mlx, t_material *mat)
{
	if (mat->texture_path)
		load_texture(mlx, mat->texture_path, &mat->color_tex);
	if (mat->bump_map_path)
		load_texture(mlx, mat->bump_map_path, &mat->bump_tex);
}

void	load_scene(void *mlx, t_scene *scene)
{
	size_t		i;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_cone		*co;

	i = 0;
	while (i < scene->spheres.size)
	{
		sp = (t_sphere *)vector_get(&scene->spheres, i++);
		load_material_textures(mlx, &sp->mat);
	}
	i = 0;
	while (i < scene->planes.size)
	{
		pl = (t_plane *)vector_get(&scene->planes, i++);
		load_material_textures(mlx, &pl->mat);
	}
	i = 0;
	while (i < scene->cylinders.size)
	{
		cy = (t_cylinder *)vector_get(&scene->cylinders, i++);
		load_material_textures(mlx, &cy->mat);
	}
	i = 0;
	while (i < scene->cones.size)
	{
		co = (t_cone *)vector_get(&scene->cones, i++);
		load_material_textures(mlx, &co->mat);
	}
}
