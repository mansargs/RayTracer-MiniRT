/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:51:26 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/05 19:59:56 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../utils/utils.h"
#include "../validation/validation.h"
#include "libft.h"
#include "vector.h"
#include "parsing_internal.h"

bool	parse_lights(char **attributes, t_vector *lights)
{
	t_light	item;
	size_t	len;

	len = count_attributes(attributes);
	if (len != 4)
		return (print_error("Light attributes count is incorrect"), false);
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY)
			&& is_valid_rgb(attributes[3])))
		return (false);
	if (!is_double(attributes[2]))
		return (print_error("Invalid double number"), false);
	item.brightness = ft_atod(attributes[2]);
	if (out_of_range(item.brightness, 0, 1))
		return (print_error("Brightness out of the range"), false);
	if (!(parse_point(attributes[1], &item.position)
			&& parse_rgb(attributes[3], &item.color)))
		return (false);
	if (!vector_push_back(lights, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}
