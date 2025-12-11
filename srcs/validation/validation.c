/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:12:04 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/12 03:00:55 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "validation.h"
#include "new_types.h"
#include "utils.h"
#include <math.h>

static bool	valid_extension(const char *path)
{
	char	*last_tree;

	if (ft_strlen(path) < 3)
	{
		ft_putendl_fd("File has invalid extension", STDERR_FILENO);
		return (false);
	}
	last_tree = ft_substr(path, ft_strlen(path) - EXTENSION_LENGTH,
			EXTENSION_LENGTH);
	if (!last_tree)
	{
		ft_putendl_fd("Problem with the memory", STDERR_FILENO);
		return (false);
	}
	if (ft_strcmp(last_tree, EXPECTED_EXTENSION) == 0)
		return (free(last_tree), true);
	free(last_tree);
	ft_putendl_fd("File has invalid extension", STDERR_FILENO);
	return (false);
}

bool	out_of_range(float num, float range_min, float range_max)
{
	return (num < range_min || num > range_max);
}

bool	all_spaces(const char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
			continue ;
		return (false);
	}
	return (true);
}

bool	is_valid_arguments(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_putendl_fd("Program must take one argument(.rt file path)",
			STDERR_FILENO);
		return (false);
	}
	if (!valid_extension(argv[1]))
		return (false);
	return (true);
}
bool	is_valid_float(const char *str)
{
	bool	has_digit;

	has_digit = false;
	if (!str || !*str)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		has_digit = true;
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			has_digit = true;
			str++;
		}
	}
	if (!has_digit)
		return (false);
	return (*str == '\0');
}

bool	is_valid_rgb(const char *str)
{
	char	**split;
	int		i;
	int		j;

	split = ft_split(str, ',');
	if (!split)
		return (ft_putendl_fd("Problem with the memory", STDERR_FILENO), false);
	i = -1;
	while (split[++i])
	{
		if (split[i][0] == '0' && split[i][1])
			return (ft_putendl_fd("Invalid rgb", 2), free_split(split), false);
		j = -1;
		while (split[i][++j])
		{
			if (!ft_isdigit(split[i][j]))
				return (ft_putendl_fd("Invalid rgb", 2), free_split(split), false);
		}
		if (ft_atoi(split[i] > 255))
			return (ft_putendl_fd("Invalid rgb", 2), free_split(split), false);
	}
	free_split(split);
	if (i != 3)
		return (ft_putendl_fd("Only r,g,b are allowed", STDERR_FILENO), false);
	return (true);
}

bool	is_valid_point(const char *str, float range_min, float range_max)
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split)
		return (ft_putendl_fd("Problem with the memory", STDERR_FILENO), false);
	i = -1;
	while (split[++i])
	{
		if (is_valid_float(split[i]) && !out_of_range(ft_atof(split[i]), range_min, range_max))
			continue ;
		free_split(split);
		ft_putendl_fd("Invalid float value or value out of allowed range.",
			STDERR_FILENO);
		return (false);
	}
	free_split(split);
	if (i != 3)
	{
		ft_putendl_fd("Only x,y,z are allowed", STDERR_FILENO);
		return (false);
	}
	return (true);
}

inline bool	is_normalized_vector(t_vec3 *p)
{
	float	len;

	len = sqrtf(p->x * p->x + p->y * p->y + p->z * p->z);
	return (fabsf(len - 1.0f) < 1e-6);
}





