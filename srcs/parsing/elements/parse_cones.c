/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cones.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:31:24 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/15 18:06:22 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../utils/utils.h"
#include "../validation/validation.h"
#include "libft.h"
#include "parsing_internal.h"

static bool	parse_cone_core(char **a, t_cone *c)
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
		return (print_error("Cone orientation vector must be normalized"),
			false);
	c->height = ft_atof(a[3]);
	if (c->height <= 0)
		return (print_error("Cone height must be positive"), false);
	c->angle = ft_atof(a[4]);
	if (c->angle <= 0 || c->angle >= 90)
		return (print_error("Cone angle must be in (0, 90)"), false);
	return (true);
}

bool	parse_cones(char **a, t_vector *cones)
{
	t_cone	item;
	size_t	len;

	len = count_attributes(a);
	if (len < 6)
		return (print_error("Cone attributes count is incorrect"), false);
	if (!parse_cone_core(a, &item))
		return (false);
	if (!parse_optional_data(a + 6, &item.mat, len - 6))
		return (material_destroy(&item.mat), false);
	if (!vector_push_back(cones, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}
