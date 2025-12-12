/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_by_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 04:46:03 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/13 00:32:02 by mansargs         ###   ########.fr       */
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
	size_t	len;

	if (ambient->is_set)
		return (print_error("File can't has many ambients"), false);
	len = count_attributes(attributes);
	if (len != 3)
		return (print_error("Ambient light attributes count is incorrect"),
			false);
	if (!is_valid_float(attributes[1]))
		return (print_error("Invalid float number"), false);
	ambient->lighting_ratio = ft_atof(attributes[1]);
	if (out_of_range(ambient->lighting_ratio, 0, 1))
		return (print_error("Ambient lighting ratio out of range"), false);
	if (!(is_valid_rgb(attributes[2]) && parse_rgb(attributes[2], &ambient->color)))
		return (false);
	ambient->is_set = true;
	return (true);
}

bool	parse_camera(char **attributes, t_camera *camera)
{
	size_t	len;

	if (camera->is_set)
		return (print_error("File can't has many cameras"), false);
	len = count_attributes(attributes);
	if (len != 4)
		return (print_error("Camera attributes count is incorrect"), false);
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY) &&
		is_valid_point(attributes[2], -1, 1)))
		return (false);
	if (!is_valid_float(attributes[3]))
		return (print_error("Invalid float number"), false);
	camera->fov = ft_atof(attributes[3]);
	if (out_of_range(camera->fov, 0, 180))
		return (print_error("FOV out of the range"), false);
	if (!(parse_point(attributes[1], &camera->position) &&
		parse_point(attributes[2], &camera->orientation)))
		return (false);
	if (!is_normalized_vector(&camera->orientation))
		return(print_error("Orientation isn't normalized"), false);
	camera->is_set = true;
	return (true);
}

bool	parse_lights(char **attributes, t_vector *lights)
{
	t_light	item;
	size_t	len;

	len = count_attributes(attributes);
	if (len != 4)
		return (print_error("Light attributes count is incorrect"), false);
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY) &&
		is_valid_rgb(attributes[3])))
		return (false);
	if (!is_valid_float(attributes[2]))
		return (print_error("Invalid float number"), false);
	item.brightness = ft_atof(attributes[2]);
	if (out_of_range(item.brightness, 0, 1))
		return (print_error("Brightness out of the range"), false);
	if (!(parse_point(attributes[1], &item.position) &&
		parse_rgb(attributes[3], &item.color)))
		return (false);
	if (!vector_push_back(lights, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}

bool parse_spheres(char **attributes, t_vector *spheres)
{
	t_sphere	item;
	size_t		len;

	len = count_attributes(attributes);
	if (len < 4)
		return (print_error("Sphere attributes count is incorrect"), false);
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY) &&
		is_valid_rgb(attributes[3])))
		return (false);
	if (!is_valid_float(attributes[2]))
		return (print_error("Invalid float number"), false);
	item.diameter = ft_atof(attributes[2]);
	if (item.diameter <= 0)
		return (print_error("Diameter must be positive"), false);
	if (!(parse_point(attributes[1], &item.center) &&
		parse_rgb(attributes[3], &item.color)))
		return (false);
	if (!parse_optional_data(attributes + 4, &item.mat, len))
		return (false);
	if (!vector_push_back(spheres, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}

bool	parse_planes(char **attributes, t_vector *planes)
{
	t_plane	item;
	size_t	len;

	len = count_attributes(attributes);
	if (len < 4)
		return (print_error("Plane attributes count is incorrect"), false);
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY) &&
		is_valid_point(attributes[2], -1, 1) &&
		is_valid_rgb(attributes[3])))
		return (false);
	if (!(parse_point(attributes[1], &item.position) &&
		parse_point(attributes[2], &item.orientation) &&
		parse_rgb(attributes[3], &item.color)))
		return (false);
	if (!is_normalized_vector(&item.orientation))
		return (print_error("Orientation vector must be normalized"), false);
	if (!parse_optional_data(attributes + 4, &item.mat, len - 4))
		return (false);
	if (!vector_push_back(planes, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}

bool parse_cones(char **attributes, t_vector *cones)
{
	t_cone	item;
	size_t	len;

	len = count_attributes(attributes);
	if (len < 5)
		return (print_error("Cone attributes count is incorrect"), false);
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY) &&
		  is_valid_point(attributes[2], -1, 1) &&
		  is_valid_rgb(attributes[5])))
		return (false);
	if (!(is_valid_float(attributes[3]) && is_valid_float(attributes[4])))
		return (print_error("Invalid float number"), false);
	if (!(parse_point(attributes[1], &item.center) &&
		  parse_point(attributes[2], &item.orientation) &&
		  parse_rgb(attributes[5], &item.color)))
		return (false);
	if (!is_normalized_vector(&item.orientation))
		return (print_error("Cone orientation vector must be normalized"), false);
	item.height = ft_atof(attributes[3]);
	if (item.height <= 0)
		return (print_error("Cone height must be positive"), false);
	item.angle = ft_atof(attributes[4]);
	if (item.angle <= 0 || item.angle >= 90)
		return (print_error("Cone angle must be in (0, 90) degrees"), false);
	if (!parse_optional_data(attributes + 6, &item.mat, len - 6))
		return (false);
	if (!vector_push_back(cones, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}


bool	parse_cylinders(char **attributes, t_vector *cylinders)
{
	t_cylinder	item;
	size_t		len;

	len = count_attributes(attributes);
	if (len < 6)
		return (print_error("Cylinder attributes count is incorrect"), false);
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY) &&
		  is_valid_point(attributes[2], -1, 1) &&
		  is_valid_rgb(attributes[5])))
		return (false);
	if (!(is_valid_float(attributes[3]) &&
		  is_valid_float(attributes[4])))
		return (print_error("Invalid float number"), false);
	if (!(parse_point(attributes[1], &item.center) &&
		  parse_point(attributes[2], &item.orientation) &&
		  parse_rgb(attributes[5], &item.color)))
		return (false);
	if (!is_normalized_vector(&item.orientation))
		return (print_error("Cylinder orientation vector must be normalized"), false);
	item.diameter = ft_atof(attributes[3]);
	if (item.diameter <= 0)
		return (print_error("Cylinder diameter must be positive"), false);
	item.height = ft_atof(attributes[4]);
	if (item.height <= 0)
		return (print_error("Cylinder height must be positive"), false);
	if (!parse_optional_data(attributes + 6, &item.mat, len - 6))
		return (false);
	if (!vector_push_back(cylinders, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}

