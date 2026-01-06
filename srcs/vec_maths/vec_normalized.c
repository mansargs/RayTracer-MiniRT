/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalized.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:21:10 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/06 20:44:21 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"

int vec_normalization(t_vec3* v)
{
	if (!v)
		return (NORMAILZATION_FAIL);
	double len = vec_magnitude(*v);
	if (len < ESP)
		return (NORMAILZATION_FAIL);
	double inv_len = 1.0 / len;
	v->x *= inv_len;
	v->y *= inv_len;
	v->z *= inv_len;
	return (NORMALIZATION_SUCCESS);
}

