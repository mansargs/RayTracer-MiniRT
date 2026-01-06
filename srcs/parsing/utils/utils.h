/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:04:41 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/05 19:47:57 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include "minirt.h"

void		material_destroy(t_material *mat);
void		print_error(char *str);
int			count_attributes(char **attr);
bool		all_spaces(const char *line);
bool		out_of_range(double num, double range_min, double range_max);
bool		parse_rgb(const char *str, t_rgb *rgb);
bool		parse_point(const char *str, t_vec3 *point);
void		free_split(char **split);

#endif
