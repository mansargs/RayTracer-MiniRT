/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cones.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:31:24 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/04 17:10:25 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "parsing_utils.h"
#include "validation.h"
#include "window.h"
#include "libft.h"
#include "parsing_internal.h"
#include "vec_math.h"

static bool	parse_cone_core(char **a, t_cone *c)
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
	if (vec_magnitude(c->orientation) < EPS)
		return (print_error("Cone orientation can't be (0,0,0) vector"), false);
	c->height = ft_atod(a[3]);
	if (c->height <= 0)
		return (print_error("Cone height must be positive"), false);
	c->angle = ft_atod(a[4]);
	if (c->angle <= 0 || c->angle >= 90)
		return (print_error("Cone angle must be in (0, 90)"), false);
	return (true);
}

bool	parse_cones(const t_window *win, char **a, t_vector *cones)
{
	t_cone	item;
	size_t	len;

	ft_memset(&item, 0, sizeof(t_sphere));
	init_default_material(&item.mat);
	len = count_attributes(a);
	if (len < 6)
		return (print_error("Cone attributes count is incorrect"), false);
	if (!parse_cone_core(a, &item))
		return (false);
	if (!parse_optional_data(a + 6, &item.mat, len - 6))
		return (material_destroy(win->mlx, &item.mat), false);
	if (!vector_push_back(cones, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}
