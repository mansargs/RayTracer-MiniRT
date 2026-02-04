/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:31:36 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/04 17:16:30 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_INTERNAL_H
# define PARSING_INTERNAL_H

# include "minirt.h"
# include "vector.h"

bool	parse_ambient_light(char **attributes, t_ambient *ambient);
bool	parse_camera(char **attributes, t_vector *camera);
bool	parse_cones(const t_window *win, char **a, t_vector *cones);
bool	parse_cylinders(const t_window *win, char **a, t_vector *cylinders);
bool	parse_lights(char **attributes, t_vector *lights);
bool	parse_optional_data(char **a, t_material *m, size_t len);
bool	parse_planes(const t_window *win, char **attr, t_vector *planes);
bool	parse_spheres(const t_window *win, char **attr, t_vector *spheres);

#endif
