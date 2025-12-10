/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:27:50 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/10 05:49:25 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "validation.h"
#include "new_types.h"
#include "vector.h"
#include "libft.h"

bool	init_scene(t_scene *scene)
{
	ft_memset(scene, '\0', sizeof(scene));
	if (!vector_init(&scene->lights, sizeof(t_light)))
		return (false);
	if (!vector_init(&scene->spheres, sizeof(t_sphere)))
		return (false);
	if (!vector_init(&scene->planes, sizeof(t_plane)))
		return (false);
	if (!vector_init(&scene->cylinders, sizeof(t_cylinder)))
		return (false);
	if (!vector_init(&scene->cones, sizeof(t_cone)))
		return (false);
	return (true);
}


int	main(int argc, char *argv[])
{
	t_scene	scene;

	if (!is_valid_arguments(argc, argv))
		return (EXIT_FAILURE);
	if (!init_scene(&scene))
		return (EXIT_FAILURE);
	parse_file(argv[1], &scene);
	free_scene(&scene);
	return (0);
}
