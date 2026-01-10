/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:49:41 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/10 18:40:56 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "parsing_utils.h"
#include "validation.h"
#include "libft.h"
#include "parsing_internal.h"
#include "vec_math.h"

bool	parse_camera(char **attributes, t_camera *camera)
{
	size_t	len;

	if (camera->is_set)
		return (print_error("File can't has many cameras"), false);
	len = count_attributes(attributes);
	if (len != 4)
		return (print_error("Camera attributes count is incorrect"), false);
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY)
			&& is_valid_point(attributes[2], -1, 1)))
		return (false);
	if (!is_double(attributes[3]))
		return (print_error("Invalid double number"), false);
	camera->fov = ft_atod(attributes[3]);
	if (out_of_range(camera->fov, 0, 180))
		return (print_error("FOV out of the range"), false);
	if (!(parse_point(attributes[1], &camera->position)
			&& parse_point(attributes[2], &camera->orientation)))
		return (false);
	if (vec_magnitude(camera->orientation) < EPS)
		return (print_error("Camera orientation can't be (0,0,0) vector"), false);
	camera->is_set = true;
	return (true);
}
