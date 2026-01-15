/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalized.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:21:10 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/15 16:07:17 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

t_vec3	vec_normalization(t_vec3 v)
{
	t_vec3	normalized;
	double	len;
	double	inv_len;

	len = vec_magnitude(v);
	if (len < EPS)
		return ((t_vec3){0.0, 0.0, 0.0});
	inv_len = 1.0 / len;
	normalized.x = v.x * inv_len;
	normalized.y = v.y * inv_len;
	normalized.z = v.z * inv_len;
	return (normalized);
}
