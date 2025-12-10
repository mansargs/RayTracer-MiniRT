/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_details.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 05:51:27 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/10 07:21:37 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_types.h"
#include "libft.h"

static bool parse_rgb_component(const char **str_ptr, int *out_num)
{
	const char	*str;

	str = *str_ptr;
	if (!*str)
		return (false);
	if (*str == '0')
	{
		*out_num = 0;
		str++;
		if (*str >= '0' && *str <= '9')
			return (false);
	}
	else
	{
		while (*str >= '0' && *str <= '9')
		{
			*out_num = *out_num * 10 + (*str - '0');
			str++;
		}
		if (*out_num > 255)
			return (false);
	}
	*str_ptr = str;
	return (true);
}

bool parse_and_validate_rgb(const char *str, t_rgb *rgb)
{
	int	count;
	int	value;

	count = 0;
	if (!str || !rgb)
		return (false);
	while (*str)
	{
		if (!parse_rgb_component(&str, &value))
			return (false);
		if (count == 0)
			rgb->r = value;
		else if (count == 1)
			rgb->g = value;
		else
			rgb->b = value;
		count++;
		if (*str == '\0')
			break;
		if (*str != ',')
			return (false);
		str++;
	}
	return (count == 3);
}

// bool	validate_and_parse_point(const char *str, t_vec3 *point,
// 			float min_range,  float max_range)
// {
// 	char	**split;

// 	split = ft_split(str, ',');
// 	if (!split)
// 	{
// 		ft_putendl_fd("Problem with the memory", STDERR_FILENO);
// 		return (false);
// 	}
// 	while()
// }
