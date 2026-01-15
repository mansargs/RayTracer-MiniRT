/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:15:53 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/15 16:49:13 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_MATH_H
# define VEC_MATH_H

# include "minirt.h"

# define EPS 1e-6

double	vec_magnitude(t_vec3 v);
t_vec3	vec_normalization(t_vec3 v);
t_vec3	vec_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec_scale(t_vec3 v1, double scale);
double	vec_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec_cross(t_vec3 v1, t_vec3 v2);

#endif
