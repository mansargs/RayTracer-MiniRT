/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_by_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 04:46:03 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/12 03:06:03 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "validation.h"
#include "new_types.h"
#include "pars.h"
#include "vector.h"
#include "utils.h"
#include <math.h>

bool	parse_ambient_light(char **attributes, t_ambient *ambient)
{
	int	len;

	if (ambient->is_set)
		return (ft_putendl_fd("File can't has many ambients", STDERR_FILENO), false);
	len = count_attributes(attributes);
	if (len != 3)
	{
		ft_putendl_fd("Ambient light attributes count is incorrect", STDERR_FILENO);
		return (false);
	}
	if (!is_valid_float(attributes[1]))
		return (ft_putendl_fd("Invalid float number", STDERR_FILENO), false);
	ambient->lighting_ratio = ft_atof(attributes[1]);
	if (out_of_range(ambient->lighting_ratio, 0, 1))
		return (ft_putendl_fd("Ambient lighting ratio out of range", STDERR_FILENO),
			false);
	if (!(is_valid_rgb(attributes[2]) && parse_rgb(attributes[2], &ambient->color)))
		return (false);
	ambient->is_set = true;
	return (true);
}

bool	parse_camera(char **attributes, t_camera *camera)
{
	int	len;

	if (camera->is_set)
		return (ft_putendl_fd("File can't has many cameras", STDERR_FILENO), false);
	len = count_attributes(attributes);
	if (len != 4)
		return (ft_putendl_fd("Camera attributes count is incorrect", STDERR_FILENO),
			false);
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY) &&
		is_valid_point(attributes[2], -1, 1)))
		return (false);
	if (!is_valid_float(attributes[3]))
		return (ft_putendl_fd("Invalid float number", STDERR_FILENO), false);
	camera->fov = ft_atof(attributes[3]);
	if (out_of_range(camera->fov, 0, 180))
		return (ft_putendl_fd("FOV out of the range", STDERR_FILENO), false);
	if (!(parse_point(attributes[1], &camera->position) &&
		parse_point(attributes[2], &camera->orientation)))
		return (false);
	if (!is_normalized_vector(&camera->orientation))
		return(ft_putendl_fd("Orientation isn't normalized", 2), false);
	camera->is_set = true;
	return (true);
}

bool	parse_lights(char **attributes, t_vector *lights)
{
	t_light	item;
	int		len;

	len = count_attributes(attributes);
	if (len != 4)
		return (ft_putendl_fd("Light attributes count is incorrect", STDERR_FILENO),
			false);
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY) &&
		is_valid_rgb(attributes[3])))
		return (false);
	if (!is_valid_float(attributes[2]))
		return (ft_putendl_fd("Invalid float number", STDERR_FILENO), false);
	item.brightness = ft_atof(attributes[2]);
	if (out_of_range(item.brightness, 0, 1))
		return (ft_putendl_fd("Brightness out of the range", STDERR_FILENO),
			false);
	if (!(parse_point(attributes[1], &item.position) &&
		parse_rgb(attributes[3], &item.color)))
		return (false);
	if (!vector_push_back(lights, &item))
		return (ft_putendl_fd("Problem with the memory", STDERR_FILENO), false);
	return (true);
}


