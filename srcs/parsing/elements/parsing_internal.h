/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:31:36 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/15 15:40:52 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_INTERNAL_H
# define PARSING_INTERNAL_H

#include "minirt.h"

bool	parse_ambient_light(char **attributes, t_ambient *ambient);
bool	parse_camera(char **attributes, t_camera *camera);
bool	parse_cones(char **a, t_vector *cones);
bool	parse_cylinders(char **a, t_vector *cylinders);
bool	parse_lights(char **attributes, t_vector *lights);
bool	parse_optional_data(char **a, t_material *m, size_t len);
bool	parse_planes(char **attr, t_vector *planes);
bool	parse_spheres(char **attr, t_vector *spheres);

#endif
