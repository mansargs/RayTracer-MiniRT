/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 03:34:23 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/15 12:57:33 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "new_types.h"
#include "vector.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	free_scene(t_scene *scene)
{
	vector_free(&scene->lights);
	vector_free(&scene->spheres);
	vector_free(&scene->planes);
	vector_free(&scene->cylinders);
	vector_free(&scene->cones);
}
