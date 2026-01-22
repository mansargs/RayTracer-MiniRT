/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:49:41 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/22 15:05:14 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "parsing_utils.h"
#include "validation.h"
#include "libft.h"
#include "parsing_internal.h"
#include "vec_math.h"
#include <stdio.h>

bool	parse_camera(char **attributes, t_vector *camera)
{
	size_t		len;
	t_camera	item;

	len = count_attributes(attributes);
	if (len != 4)
		return (print_error("Camera attributes count is incorrect"), false);
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY)
			&& is_valid_point(attributes[2], -1, 1)))
		return (false);
	if (!is_double(attributes[3]))
		return (print_error("Invalid double number"), false);
	item.fov = ft_atod(attributes[3]);
	if (out_of_range(item.fov, 0, 180))
		return (print_error("FOV out of the range"), false);
	if (!(parse_point(attributes[1], &item.position)
			&& parse_point(attributes[2], &item.orientation)))
		return (false);
	if (vec_magnitude(item.orientation) < EPS)
		return (print_error("Camera orientation can't be (0,0,0) vector"),
			false);
	if (!vector_push_back(camera, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}
