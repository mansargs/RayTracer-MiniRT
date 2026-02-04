/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_optional.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:07:47 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/04 19:11:16 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "parsing_utils.h"
#include "validation.h"
#include "libft.h"
#include "parsing_internal.h"

static bool	parse_specular_core(char **attributes, t_specular *spec)
{
	if (!is_double(attributes[0]))
		return (print_error("Specular: k_s must be a double 0–1"), false);
	if (!is_integer(attributes[1]))
		return (print_error("Specular: n_s must be an integer 1–1000"), false);
	spec->k_s = ft_atod(attributes[0]);
	spec->n_s = ft_atoi(attributes[1]);
	if (out_of_range(spec->k_s, 0, 1))
		return (print_error("Specular: k_s out of range 0–1"), false);
	if (out_of_range(spec->n_s, 1, 1000))
		return (print_error("Specular: n_s out of range 1–1000"), false);
	return (true);
}

static bool	parse_texture_core(char **filename, const char *path)
{
	if (!valid_extension(path, TEXTURE_EXTENSION))
		return (print_error("Texture or bump map can be only .xpm"), false);
	*filename = ft_strdup(path);
	if (!*filename)
		return (print_error("Memory allocation problem"), false);
	return (true);
}

static int	parse_opt_specular(char **a, t_material *m, size_t i, size_t len)
{
	if (!(is_double(a[i]) && i + 1 < len && is_integer(a[i + 1])))
		return (0);
	if (m->has_specular == true)
		return (print_error("Duplicate specular"), -1);
	if (!parse_specular_core(&a[i], &m->spec))
		return (-1);
	return (2);
}

static int	parse_opt_texture(char *attr, t_material *m)
{
	if (!valid_extension(attr, TEXTURE_EXTENSION))
		return (0);
	if (!m->texture_path)
		return (parse_texture_core(&m->texture_path, attr), 1);
	if (!m->bump_map_path)
		return (parse_texture_core(&m->bump_map_path, attr), 1);
	return (print_error("Too many textures"), -1);
}

#include <stdio.h>

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
		{
			m->has_specular = true;
			i += step;
		}
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
