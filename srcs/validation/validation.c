/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:12:04 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/10 02:18:19 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "validation.h"
#include <stdbool.h>

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
	if (ft_strncmp(last_tree, EXPECTED_EXTENSION, EXTENSION_LENGTH) == 0)
		return (free(last_tree), true);
	free(last_tree);
	ft_putendl_fd("File has invalid extension", STDERR_FILENO);
	return (false);
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
	if (argc != 2 || !valid_extension(argv[1]))
	{
		ft_putendl_fd("Program must take one argument(.rt file path)",
			STDERR_FILENO);
		return (false);
	}
	return (true);
}
