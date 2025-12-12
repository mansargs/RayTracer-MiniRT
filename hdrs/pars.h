/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:23:35 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/12 23:01:50 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H

#include "new_types.h"

bool	parse_rgb(const char *str, t_rgb *rgb);
bool	parse_point(const char *str, t_vec3 *point);
bool	parse_optional_data(char **attributes, t_material *mat, size_t len);
bool	parse_file(const char *path, t_scene *scene);
bool	parse_ambient_light(char **attributes, t_ambient *ambient);
bool	parse_camera(char **attributes, t_camera *camera);
bool	parse_lights(char **attributes, t_vector *lights);
bool	parse_spheres(char **attributes, t_vector *spheres);
bool	parse_planes(char **attributes, t_vector *planes);
bool	parse_cones(char **attributes, t_vector *cones);
bool	parse_cylinders(char **attributes, t_vector *cylinders);

#endif
