/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:18:24 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/12 03:01:41 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# define EXPECTED_EXTENSION ".rt"
# define EXTENSION_LENGTH 3

# include <stdbool.h>

bool		all_spaces(const char *line);
bool		is_valid_arguments(int argc, char *argv[]);
bool		is_valid_float(const char *str);
bool		is_valid_point(const char *str, float range_min, float range_max);
bool		is_valid_rgb(const char *str);
inline bool	is_normalized_vector(t_vec3 *p);
inline bool	out_of_range(float num, float range_min, float range_max);

#endif
