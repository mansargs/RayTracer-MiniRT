/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_magnitude.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:13:43 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/06 19:56:52 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec_math.h"
#include <math.h>

double vec_magnitude(t_vec3 v) {
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
