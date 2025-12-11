/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:23:35 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/11 19:24:56 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARS_H
# define PARS_H

#include "new_types.h"

bool	parse_rgb(const char *str, t_rgb *rgb);
bool	parse_point(const char *str, t_vec3 *point);

#endif
