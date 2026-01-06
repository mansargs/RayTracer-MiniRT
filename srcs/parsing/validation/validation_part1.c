/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_part1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:06:29 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/05 19:47:57 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../utils/utils.h"
#include "validation.h"
#include <math.h>

bool	valid_extension(const char *path, const char *extension)
{
	size_t	extension_len;
	size_t	path_len;

	if (!path || !extension)
		return (false);
	extension_len = ft_strlen(extension);
	path_len = ft_strlen(path);
	if (path_len < extension_len)
		return (false);
	path += path_len - extension_len;
	if (ft_strcmp(path, extension) == 0)
		return (true);
	return (false);
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
	{
		ft_putendl_fd("File has invalid extension", STDERR_FILENO);
		return (false);
	}
	return (true);
}

bool	is_double(const char *str)
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
