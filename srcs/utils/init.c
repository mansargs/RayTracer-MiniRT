/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:18:24 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/15 18:20:11 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

bool	init_scene(t_scene *scene)
{
	ft_memset(scene, 0, sizeof(*scene));
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


