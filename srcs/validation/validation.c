/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:12:04 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/13 00:30:36 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "validation.h"
#include "new_types.h"
#include "utils.h"
#include <math.h>

bool	valid_extension(const char *path, const char *extension)
{
	char	*s;
	size_t	extension_len;

	extension_len = ft_strlen(extension);
	if (ft_strlen(path) < extension_len)
	{
		ft_putendl_fd("File has invalid extension", STDERR_FILENO);
		return (false);
	}
	s = ft_substr(path, ft_strlen(path) - extension_len,
			extension_len);
	if (!s)
	{
		ft_putendl_fd("Problem with the memory", STDERR_FILENO);
		return (false);
	}
	if (ft_strcmp(s, extension) == 0)
		return (free(s), true);
	free(s);
	ft_putendl_fd("File has invalid extension", STDERR_FILENO);
	return (false);
}

inline bool	out_of_range(float num, float range_min, float range_max)
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
	if (!valid_extension(argv[1], FILE_EXTENSION))
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

bool is_valid_rgb(const char *str)
{
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split)
		return (print_error("Memory allocation problem"), false);
	if (count_attributes(split) != 3)
		return (free_split(split), print_error("RGB needs exactly 3 numbers"), false);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_integer(split[i]) || ft_atoi(split[i]) > 255)
			return (free_split(split), print_error("Invalid RGB value"), false);
		i++;
	}
	free_split(split);
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
		print_error("Invalid float value or value out of allowed range.");
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

bool	is_valid_integer(const char *str)
{
	if (*str == '\0')
		return (false);
	if (*str == '-' || *str == '+')
		++str;
	if (*str == '0' && *(str + 1))
		return (false);
	while (*str)
	{
		// write(1, str, 1);
		if (!ft_isdigit(*str))
			return (false);
		++str;
	}
	return (true);
}


