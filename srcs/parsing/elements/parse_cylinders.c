/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:07:35 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/15 16:07:38 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../utils/utils.h"
#include "../validation/validation.h"
#include "libft.h"
#include "parsing_internal.h"

static bool	parse_cylinder_core(char **a, t_cylinder *c)
{
	if (!(is_valid_point(a[1], -INFINITY, INFINITY)
			&& is_valid_point(a[2], -1, 1)
			&& is_valid_rgb(a[5])))
		return (false);
	if (!(is_float(a[3]) && is_float(a[4])))
		return (print_error("Invalid float number"), false);
	if (!(parse_point(a[1], &c->center)
			&& parse_point(a[2], &c->orientation)
			&& parse_rgb(a[5], &c->color)))
		return (false);
	if (!is_normalized_vector(&c->orientation))
		return (print_error("Cylinder orientation vector must be normalized"),
			false);
	c->diameter = ft_atof(a[3]);
	if (c->diameter <= 0)
		return (print_error("Cylinder diameter must be positive"), false);
	c->height = ft_atof(a[4]);
	if (c->height <= 0)
		return (print_error("Cylinder height must be positive"), false);
	return (true);
}

bool	parse_cylinders(char **a, t_vector *cylinders)
{
	t_cylinder	item;
	size_t		len;

	len = count_attributes(a);
	if (len < 6)
		return (print_error("Cylinder attributes count is incorrect"), false);
	if (!parse_cylinder_core(a, &item))
		return (false);
	if (!parse_optional_data(a + 6, &item.mat, len - 6))
		return (false);
	if (!vector_push_back(cylinders, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}
