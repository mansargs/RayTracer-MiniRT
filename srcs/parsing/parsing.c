/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:54:33 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/12 02:05:50 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "validation.h"
#include <stdbool.h>
#include "new_types.h"
#include"utils.h"

bool	parse_based_on_type(char **attributes, t_scene *scene)
{
	if (ft_strcmp(attributes[0], "A") == 0)
		return (parse_ambient_light(attributes, scene->ambient));
	else if (ft_strcmp(attributes[0], "C") == 0)
		return (parse_camera(attributes, scene->camera));
	else if (ft_strcmp(attributes[0], "L") == 0)
		return (parse_lights(attributes, scene->lights));
	else if (ft_strcmp(attributes[0], "sp") == 0)
		return (parse_sphere(attributes, scene));
	else if (ft_strcmp(attributes[0], "pl") == 0)
		return (parse_plane(attributes, scene));
	else if (ft_strcmp(attributes[0], "cy") == 0)
		return (parse_cylinder(attributes, scene));
	else if (ft_strcmp(attributes[0], "co") == 0)
		return (parse_cone(attributes, scene));
	else
	{
		ft_putendl_fd("Unknown identifier", STDERR_FILENO);
		return (false);
	}
}

bool	parse_line(const char *line, t_scene *scene)
{
	char	**attributes;
	bool	ret_value;

	ret_value = true;
	if(all_spaces(line))
		return (true);
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

bool	parse_loop(int fd, t_scene *scene)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		ft_putendl_fd("File is empty", STDERR_FILENO);
		return (false);
	}
	while (line)
	{
		if (!parse_line(line, scene))
			return (free(line), false);
		free(line);
		line = get_next_line(fd);
	}
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
	return (false);
}
