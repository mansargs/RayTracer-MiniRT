/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_details.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 05:51:27 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/15 13:08:23 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "new_types.h"
#include "validation.h"
#include "utils.h"
#include "libft.h"

static bool	parse_specular(char **attributes, t_specular *spec)
{
	if (!is_float(attributes[0]))
		return (print_error("Specular: k_s must be a float 0–1"), false);
	if (!is_integer(attributes[1]))
		return (print_error("Specular: n_s must be an integer 1–1000"), false);
	spec->k_s = ft_atof(attributes[0]);
	spec->n_s = ft_atoi(attributes[1]);
	if (out_of_range(spec->k_s, 0, 1))
		return (print_error("Specular: k_s out of range 0–1"), false);
	if (out_of_range(spec->n_s, 1, 1000))
		return (print_error("Specular: n_s out of range 1–1000"), false);
	return (true);
}

static bool	parse_texture(char **filename, const char *path)
{
	if (!valid_extension(path, TEXTURE_EXTENSION))
		return (print_error("Texture or bump map can be only .xpm"), false);
	*filename = ft_strdup(path);
	if (!*filename)
		return (print_error("Memory allocation problem"), false);
	return (true);
}

int	parse_opt_specular(char **a, t_material *m, size_t i, size_t len)
{
	if (!(is_float(a[i]) && i + 1 < len && is_integer(a[i + 1])))
		return (0);
	if (m->spec.k_s != -1)
		return (print_error("Duplicate specular"), -1);
	if (!parse_specular(&a[i], &m->spec))
		return (-1);
	return (2);
}

int	parse_opt_texture(char *attr, t_material *m)
{
	if (!valid_extension(attr, TEXTURE_EXTENSION))
		return (0);
	if (!m->texture_path)
		return (parse_texture(&m->texture_path, attr), 1);
	if (!m->bump_map_path)
		return (parse_texture(&m->bump_map_path, attr), 1);
	return (print_error("Too many textures"), -1);
}

bool	parse_optional_data(char **a, t_material *m, size_t len)
{
	size_t	i;
	int		step;

	i = 0;
	while (i < len)
	{
		step = parse_opt_specular(a, m, i, len);
		if (step < 0)
			return (false);
		if (step > 0)
			i += step;
		else
		{
			step = parse_opt_texture(a[i], m);
			if (step <= 0)
				return (print_error("Optional attributes are incorrect"),
					false);
			i += step;
		}
	}
	return (true);
}

bool	parse_rgb(const char *str, t_rgb *rgb)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (print_error("Memory allocation problem"), false);
	rgb->r = ft_atoi(split[0]);
	rgb->g = ft_atoi(split[1]);
	rgb->b = ft_atoi(split[2]);
	free_split(split);
	return (true);
}

bool	parse_point(const char *str, t_vec3 *point)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (print_error("Memory allocation problem"), false);
	point->x = ft_atof(split[0]);
	point->y = ft_atof(split[1]);
	point->z = ft_atof(split[2]);
	free_split(split);
	return (true);
}
