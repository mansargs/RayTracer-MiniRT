/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:32:19 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/05 19:59:56 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "../validation/validation.h"
#include "libft.h"
#include "parsing_internal.h"

bool	parse_ambient_light(char **attributes, t_ambient *ambient)
{
	size_t	len;

	if (ambient->is_set)
		return (print_error("File can't has many ambients"), false);
	len = count_attributes(attributes);
	if (len != 3)
		return (print_error("Ambient light attributes count is incorrect"),
			false);
	if (!is_double(attributes[1]))
		return (print_error("Invalid double number"), false);
	ambient->lighting_ratio = ft_atod(attributes[1]);
	if (out_of_range(ambient->lighting_ratio, 0, 1))
		return (print_error("Ambient lighting ratio out of range"), false);
	if (!(is_valid_rgb(attributes[2])
			&& parse_rgb(attributes[2], &ambient->color)))
		return (false);
	ambient->is_set = true;
	return (true);
}
