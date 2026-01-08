/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:04:41 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/08 18:04:18 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

# include <stdbool.h>
# include "minirt.h"

void		material_destroy(t_material *mat);
void		init_default_material(t_material* mat);
void		print_error(char *str);
int			count_attributes(char **attr);
bool		all_spaces(const char *line);
bool		out_of_range(double num, double range_min, double range_max);
bool		parse_rgb(const char *str, t_rgb *rgb);
bool		parse_point(const char *str, t_vec3 *point);
void		free_split(char **split);

#endif
