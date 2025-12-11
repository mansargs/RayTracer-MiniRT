/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_details.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 05:51:27 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/11 19:08:28 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_types.h"
#include "validation.h"
#include "utils.h"
#include "libft.h"

bool	parse_rgb(const char *str, t_rgb *rgb)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (ft_putendl_fd("Problem with the memory", STDERR_FILENO), false);
	rgb->r = split[0];
	rgb->g = split[1];
	rgb->b = split[2];
	free_split(split);
	return (true);
}

bool	parse_point(const char *str, t_vec3 *point)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (ft_putendl_fd("Problem with the memory", STDERR_FILENO), false);
	point->x = ft_atof(split[0]);
	point->y = ft_atof(split[1]);
	point->z = ft_atof(split[2]);
	free_split(split);
	return (true);
}

