/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:07:35 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/08 18:10:12 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "parsing_utils.h"
#include "validation.h"
#include "libft.h"
#include "parsing_internal.h"
#include "vec_math.h"

static bool	parse_cylinder_core(char **a, t_cylinder *c)
{
	if (!(is_valid_point(a[1], -INFINITY, INFINITY)
			&& is_valid_point(a[2], -1, 1)
			&& is_valid_rgb(a[5])))
		return (false);
	if (!(is_double(a[3]) && is_double(a[4])))
		return (print_error("Invalid double number"), false);
	if (!(parse_point(a[1], &c->center)
			&& parse_point(a[2], &c->orientation)
			&& parse_rgb(a[5], &c->color)))
		return (false);
	if (vec_normalization(&c->orientation) == NORMAILZATION_FAIL)
		return (print_error("Cylinder orientation can't be (0,0,0) vector"),
			false);
	c->radius = ft_atod(a[3]) / 2;
	if (c->radius <= 0)
		return (print_error("Cylinder radius must be positive"), false);
	c->height = ft_atod(a[4]);
	if (c->height <= 0)
		return (print_error("Cylinder height must be positive"), false);
	return (true);
}

bool	parse_cylinders(char **a, t_vector *cylinders)
{
	t_cylinder	item;
	size_t		len;

	ft_memset(&item, 0, sizeof(t_sphere));
	init_default_material(&item.mat);
	len = count_attributes(a);
	if (len < 6)
		return (print_error("Cylinder attributes count is incorrect"), false);
	if (!parse_cylinder_core(a, &item))
		return (false);
	if (!parse_optional_data(a + 6, &item.mat, len - 6))
		return (material_destroy(&item.mat), false);
	if (!vector_push_back(cylinders, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}
