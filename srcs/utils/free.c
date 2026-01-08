/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:11:41 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/08 18:01:43 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "vector.h"
#include <stdlib.h>

void	material_destroy(t_material *mat)
{
	if (!mat)
		return;
	free(mat->texture_path);
	free(mat->bump_map_path);
	mat->texture_path = NULL;
	mat->bump_map_path = NULL;
	mat->has_specular = false;
}

static void	free_vector_materials(t_vector *vec, size_t material_offset)
{
	size_t	i;
	char	*base;

	i = 0;
	while (i < vec->size)
	{
		base = (char *)vector_get(vec, i);
		material_destroy((t_material *)(base + material_offset));
		i++;
	}
}

void	free_scene(t_scene *scene)
{
	free_vector_materials(&scene->spheres, offsetof(t_sphere, mat));
	free_vector_materials(&scene->planes, offsetof(t_plane, mat));
	free_vector_materials(&scene->cylinders, offsetof(t_cylinder, mat));
	free_vector_materials(&scene->cones, offsetof(t_cone, mat));

	vector_free(&scene->lights);
	vector_free(&scene->spheres);
	vector_free(&scene->planes);
	vector_free(&scene->cylinders);
	vector_free(&scene->cones);
}
