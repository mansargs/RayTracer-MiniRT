/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:11:41 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/04 17:46:17 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "vector.h"
#include "window.h"
#include "mlx.h"
#include <stdlib.h>

void	material_destroy(void *mlx, t_material *mat)
{
	if (!mat)
		return ;
	free(mat->texture_path);
	free(mat->bump_map_path);
	if (mlx && mat->color_tex.img)
		mlx_destroy_image(mlx, mat->color_tex.img);
	if (mlx && mat->bump_tex.img)
		mlx_destroy_image(mlx, mat->bump_tex.img);
	mat->texture_path = NULL;
	mat->bump_map_path = NULL;
	mat->has_specular = false;
}

static void	free_vector_materials(void *mlx, t_vector *vec, size_t material_offset)
{
	size_t	i;
	char	*base;

	i = 0;
	while (i < vec->size)
	{
		base = (char *)vector_get(vec, i);
		material_destroy(mlx, (t_material *)(base + material_offset));
		i++;
	}
}

void	free_scene(void *mlx, t_scene *scene)
{
	if (!scene)
		return ;
	free_vector_materials(mlx, &scene->spheres, offsetof(t_sphere, mat));
	free_vector_materials(mlx, &scene->planes, offsetof(t_plane, mat));
	free_vector_materials(mlx, &scene->cylinders, offsetof(t_cylinder, mat));
	free_vector_materials(mlx, &scene->cones, offsetof(t_cone, mat));
	vector_free(&scene->lights);
	vector_free(&scene->spheres);
	vector_free(&scene->planes);
	vector_free(&scene->cylinders);
	vector_free(&scene->cones);
	vector_free(&scene->camera);

}
