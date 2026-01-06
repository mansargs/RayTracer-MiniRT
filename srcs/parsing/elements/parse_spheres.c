/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spheres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:08:40 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/05 19:59:56 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../utils/utils.h"
#include "../validation/validation.h"
#include "libft.h"
#include "parsing_internal.h"


bool	parse_sphere_core(char **attr, t_sphere *item)
{
	if (!(is_valid_point(attr[1], -INFINITY, INFINITY)
			&& is_valid_rgb(attr[3])))
		return (false);
	if (!is_double(attr[2]))
		return (print_error("Invalid double number"), false);
	item->radius = ft_atod(attr[2]) / 2;
	if (item->radius <= 0)
		return (print_error("radius must be positive"), false);
	if (!(parse_point(attr[1], &item->center)
			&& parse_rgb(attr[3], &item->color)))
		return (false);
	return (true);
}

bool	parse_spheres(char **attr, t_vector *spheres)
{
	t_sphere	item;
	size_t		len;

	len = count_attributes(attr);
	if (len < 4)
		return (print_error("Sphere attributes count is incorrect"), false);
	if (!parse_sphere_core(attr, &item))
		return (false);
	if (!parse_optional_data(attr + 4, &item.mat, len - 4))
		return (material_destroy(&item.mat), false);
	if (!vector_push_back(spheres, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}
