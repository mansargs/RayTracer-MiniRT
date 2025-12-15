/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:18:24 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/15 11:34:09 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# define FILE_EXTENSION ".rt"
# define TEXTURE_EXTENSION ".xpm"

# include <stdbool.h>
# include "new_types.h"

bool		all_spaces(const char *line);
bool		is_valid_arguments(int argc, char *argv[]);
bool		is_float(const char *str);
bool		is_valid_point(const char *str, float range_min, float range_max);
bool		is_valid_rgb(const char *str);
bool		is_normalized_vector(t_vec3 *p);
bool		out_of_range(float num, float range_min, float range_max);
bool		is_integer(const char *str);
bool		valid_extension(const char *path, const char *extension);

#endif
