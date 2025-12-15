/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_by_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 04:46:03 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/15 13:05:33 by mansargs         ###   ########.fr       */
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
	if (!is_float(attributes[1]))
		return (print_error("Invalid float number"), false);
	ambient->lighting_ratio = ft_atof(attributes[1]);
	if (out_of_range(ambient->lighting_ratio, 0, 1))
		return (print_error("Ambient lighting ratio out of range"), false);
	if (!(is_valid_rgb(attributes[2])
			&& parse_rgb(attributes[2], &ambient->color)))
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
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY)
			&& is_valid_point(attributes[2], -1, 1)))
		return (false);
	if (!is_float(attributes[3]))
		return (print_error("Invalid float number"), false);
	camera->fov = ft_atof(attributes[3]);
	if (out_of_range(camera->fov, 0, 180))
		return (print_error("FOV out of the range"), false);
	if (!(parse_point(attributes[1], &camera->position)
			&& parse_point(attributes[2], &camera->orientation)))
		return (false);
	if (!is_normalized_vector(&camera->orientation))
		return (print_error("Orientation isn't normalized"), false);
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
	if (!(is_valid_point(attributes[1], -INFINITY, INFINITY)
			&& is_valid_rgb(attributes[3])))
		return (false);
	if (!is_float(attributes[2]))
		return (print_error("Invalid float number"), false);
	item.brightness = ft_atof(attributes[2]);
	if (out_of_range(item.brightness, 0, 1))
		return (print_error("Brightness out of the range"), false);
	if (!(parse_point(attributes[1], &item.position)
			&& parse_rgb(attributes[3], &item.color)))
		return (false);
	if (!vector_push_back(lights, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}

bool	parse_sphere_core(char **attr, t_sphere *item)
{
	if (!(is_valid_point(attr[1], -INFINITY, INFINITY)
			&& is_valid_rgb(attr[3])))
		return (false);
	if (!is_float(attr[2]))
		return (print_error("Invalid float number"), false);
	item->diameter = ft_atof(attr[2]);
	if (item->diameter <= 0)
		return (print_error("Diameter must be positive"), false);
	if (!(parse_point(attr[1], &item->center)
			&& parse_rgb(attr[3], &item->color)))
		return (false);
}

bool	parse_spheres(char **attr, t_vector *spheres)
{
	t_sphere	item;
	size_t		len;

	len = count_attributes(attr);
	if (len < 4)
		return (print_error("Sphere attributes count is incorrect"), false);
	if (!parse_sphere_core(attr, &item))
		return (false);
	if (!parse_optional_data(attr + 4, &item.mat, len))
		return (false);
	if (!vector_push_back(spheres, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}

static bool	parse_plane_core(char **attr, t_plane *p)
{
	if (!(is_valid_point(attr[1], -INFINITY, INFINITY)
			&& is_valid_point(attr[2], -1, 1)
			&& is_valid_rgb(attr[3])))
		return (false);
	if (!(parse_point(attr[1], &p->position)
			&& parse_point(attr[2], &p->orientation)
			&& parse_rgb(attr[3], &p->color)))
		return (false);
	if (!is_normalized_vector(&p->orientation))
		return (print_error("Orientation vector must be normalized"), false);
	return (true);
}

bool	parse_planes(char **attr, t_vector *planes)
{
	t_plane	item;
	size_t	len;

	len = count_attributes(attr);
	if (len < 4)
		return (print_error("Plane attributes count is incorrect"), false);
	if (!parse_plane_core(attr, &item))
		return (false);
	if (!parse_optional_data(attr + 4, &item.mat, len - 4))
		return (false);
	if (!vector_push_back(planes, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}

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
		return (false);
	if (!vector_push_back(cones, &item))
		return (print_error("Memory allocation problem"), false);
	return (true);
}

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
