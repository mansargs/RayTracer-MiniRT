/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:51:43 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/10 18:42:09 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include <math.h>

t_quad	solve_quadratic(t_quad_coeffs coeffs)
{
	t_quad	result;
	double	disc;
	double	sqrt_disc;

	disc = coeffs.b * coeffs.b - 4.0 * coeffs.a * coeffs.c;
	if (disc < 0)
	{
		result.has_solution = false;
		return (result);
	}
	else
	{
		result.has_solution = true;
		sqrt_disc = sqrt(disc);
		result.t1 = (-coeffs.b - sqrt_disc) / (2.0 *coeffs.a);
		result.t2 = (-coeffs.b + sqrt_disc) / (2.0 *coeffs.a);
	}
	return (result);
}
