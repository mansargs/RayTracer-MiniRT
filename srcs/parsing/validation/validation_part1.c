/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_part1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot <copilot@example.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15  GitHub Copilot                 #+#    #+#             */
/*   Updated: 2025/12/15  GitHub Copilot                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../utils/utils.h"
#include "validation.h"
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

bool	is_float(const char *str)
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
