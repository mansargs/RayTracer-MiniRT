/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:39:29 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/15 15:45:08 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "validation/validation.h"
#include "utils/utils.h"
#include "elements/parsing_internal.h"
#include "minirt.h"

static bool	parse_based_on_type(char **attributes, t_scene *scene)
{
	if (ft_strcmp(attributes[0], "A") == 0)
		return (parse_ambient_light(attributes, &scene->ambient));
	else if (ft_strcmp(attributes[0], "C") == 0)
		return (parse_camera(attributes, &scene->camera));
	else if (ft_strcmp(attributes[0], "L") == 0)
		return (parse_lights(attributes, &scene->lights));
	else if (ft_strcmp(attributes[0], "sp") == 0)
		return (parse_spheres(attributes, &scene->spheres));
	else if (ft_strcmp(attributes[0], "pl") == 0)
		return (parse_planes(attributes, &scene->planes));
	else if (ft_strcmp(attributes[0], "cy") == 0)
		return (parse_cylinders(attributes, &scene->cylinders));
	else if (ft_strcmp(attributes[0], "co") == 0)
		return (parse_cones(attributes, &scene->cones));
	else
	{
		ft_putendl_fd("Unknown identifier", STDERR_FILENO);
		return (false);
	}
}

static bool	parse_line(char *line, t_scene *scene, size_t *len)
{
	char	**attributes;
	bool	ret_value;

	ret_value = true;
	if (all_spaces(line))
		return (true);
	*len = ft_strlen(line);
	line[*len - 1] = '\0';
	attributes = ft_split(line, ' ');
	if (!attributes)
	{
		ft_putendl_fd("Problem with the memory", STDERR_FILENO);
		return (false);
	}
	if (!parse_based_on_type(attributes, scene))
		ret_value = false;
	free_split(attributes);
	return (ret_value);
}

static bool	parse_loop(int fd, t_scene *scene)
{
	char	*line;
	size_t	len;

	len = 0;
	line = get_next_line(fd);
	if (!line)
	{
		ft_putendl_fd("File is empty", STDERR_FILENO);
		return (false);
	}
	if (!all_spaces(line))
	{
		len = ft_strlen(line);
		line[len - 1] = '\0';
	}
	while (line)
	{
		if (!parse_line(line, scene, &len))
			return (free(line), false);
		free(line);
		line = get_next_line(fd);
	}
	if (len == 0)
		return (print_error("The file contains only spaces"), false);
	return (true);
}

bool	parse_file(const char *path, t_scene *scene)
{
	int		fd;
	bool	ret;

	ret = true;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Program can't open file", STDERR_FILENO);
		return (false);
	}
	if (!parse_loop(fd, scene))
		ret = false;
	close(fd);
	if (scene->ambient.is_set == false || scene->camera.is_set == false
		|| scene->lights.size == 0)
	{
		ret = false;
		print_error("File must have 1 camera, 1 ambient and light(s)");
	}
	return (ret);
}
