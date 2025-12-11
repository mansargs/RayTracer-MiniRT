/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_by_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 04:46:03 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/11 20:06:33 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "validation.h"
#include "new_types.h"
#include "pars.h"
#include <float.h>

bool	parse_ambient_light(char **attributes, t_ambient *ambient)
{
	int	len;

	if (ambient->is_set)
		return (ft_putendl_fd("File can't has many ambients", STDERR_FILENO), false);
	len = -1;
	while (attributes[++len]);
	if (len > 3)
	{
		ft_putendl_fd("Ambient light attributes count is incorrect", STDERR_FILENO);
		return (false);
	}
	if (!is_valid_float(attributes[1]))
		return (ft_putendl_fd("Invalid float number", STDERR_FILENO), false);
	ambient->lighting_ratio = ft_atof(attributes[1]);
	if (!(is_valid_rgb(attributes[1]) && parse_rgb(attributes[1], ambient)))
		return (false);
	ambient->is_set = true;
	return (true);
}

bool	parse_camera(char **attriibutes, t_camera *camera)
{
	int	i;

	if (camera->is_set)
		return (ft_putendl_fd("File can't has many cameras", STDERR_FILENO), false);
	i = -1;
	while (attriibutes[++i]);
	if (i > 4)
		return (ft_putendl_fd("Camera attributes count is incorrect", STDERR_FILENO),
			false);
	if (!(is_valid_point(attriibutes[1], FLT_MIN, FLT_MAX) &&
		is_valid_point(attriibutes[2], -1, 1)))
		return (false);
	if (!is_valid_float(attriibutes[3]))
		return (ft_putendl_fd("Invalid float number", STDERR_FILENO), false);
	camera->fov = ft_atof(attriibutes[3]);
	if (camera->fov < 0 || camera->fov > 180)
		return (ft_putendl_fd("Invalid fov", STDERR_FILENO), false);
	if (!(parse_point(attriibutes[1], &camera->position) &&
		parse_point(attriibutes[2], &camera->orientation)))
		return (false);
	return (true);
}
