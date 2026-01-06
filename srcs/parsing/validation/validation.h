/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:14:21 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/05 21:44:47 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# define TEXTURE_EXTENSION ".xpm"
# define FILE_EXTENSION ".rt"

# include "minirt.h"

bool		valid_extension(const char *path, const char *extension);
bool		is_valid_arguments(int argc, char *argv[]);
bool		is_double(const char *str);
bool		is_integer(const char *str);
bool		is_valid_rgb(const char *str);
bool		is_valid_point(const char *str, double range_min, double range_max);

#endif
