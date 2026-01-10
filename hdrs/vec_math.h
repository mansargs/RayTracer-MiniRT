/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:15:53 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/10 18:40:31 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_MATHS_H
# define VEC_MATHS_H

#include "minirt.h"

# define EPS 1e-6

double	vec_magnitude(t_vec3 v);
t_vec3	vec_normalization(t_vec3 v);
t_vec3	vec_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec_scale(t_vec3 v1, double scale);
double	vec_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec_cross(t_vec3 v1, t_vec3 v2);

#endif
