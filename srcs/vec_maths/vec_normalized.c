/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalized.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:21:10 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/06 20:28:34 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

int vec_normalization(t_vec3* point)
{
	if (!point)
		return (-1);
	double len = vec_magnitude(point);
	if (len < ESP)
		return (NORMAILZATION_FAIL);
	double inv_len = 1.0 / len;
	point->x *= inv_len;
	point->y *= inv_len;
	point->z *= inv_len;
	return (NORMALIZATION_SUCCESS);
}

