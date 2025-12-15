/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_part2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot <copilot@example.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15  GitHub Copilot                 #+#    #+#             */
/*   Updated: 2025/12/15  GitHub Copilot                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../utils/utils.h"
#include <math.h>

bool	is_valid_rgb(const char *str)
{
    char	**split;
    int		i;

    if (!str)
        return (print_error("NULL input for RGB"), false);
    split = ft_split(str, ',');
    if (!split)
        return (print_error("Memory allocation problem"), false);
    if (count_attributes(split) != 3)
        return (free_split(split), print_error("RGB needs exactly 3 numbers"),
            false);
    i = 0;
    while (i < 3)
    {
        if (!is_integer(split[i]) || out_of_range(ft_atoi(split[i]), 0, 255))
        {
            free_split(split);
            print_error("Invalid RGB value");
            return (false);
        }
        i++;
    }
    free_split(split);
    return (true);
}

bool	is_valid_point(const char *str, float range_min, float range_max)
{
    char	**split;
    int		i;

    if (!str)
        return (print_error("NULL input for point"), false);
    split = ft_split(str, ',');
    if (!split)
        return (ft_putendl_fd("Problem with the memory", STDERR_FILENO), false);
    if (count_attributes(split) != 3)
        return (free_split(split), print_error("Point needs exactly 3 numbers"),
            false);
    i = 0;
    while (i < 3)
    {
        if (!is_float(split[i])
            || out_of_range(ft_atof(split[i]), range_min, range_max))
        {
            free_split(split);
            print_error("Invalid float value or value out of allowed range.");
            return (false);
        }
        i++;
    }
    free_split(split);
    return (true);
}

inline bool	is_normalized_vector(t_vec3 *p)
{
    float	len;

    len = sqrtf(p->x * p->x + p->y * p->y + p->z * p->z);
    return (fabsf(len - 1.0f) < 1e-6);
}

bool	is_integer(const char *str)
{
    if (*str == '\0')
        return (false);
    if (*str == '-' || *str == '+')
        ++str;
    if (*str == '0' && *(str + 1))
        return (false);
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (false);
        ++str;
    }
    return (true);
}
