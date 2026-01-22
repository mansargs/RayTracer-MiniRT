/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:13:51 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/22 12:41:18 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "intersection.h"
#include "phong.h"
#include "math.h"

t_rgb	compute_ambient(const t_hit *hit, const t_ambient *ambient)
{
	t_rgb	result;
	t_rgb	surface_color;

	result = (t_rgb){0.0, 0.0, 0.0};
	surface_color = find_surface_color(hit);
	result.r = (surface_color.r / 255.0) * (ambient->color.r / 255.0)
		* ambient->lighting_ratio * 255.0;
	result.g = (surface_color.g / 255.0) * (ambient->color.g / 255.0)
		* ambient->lighting_ratio * 255.0;
	result.b = (surface_color.b / 255.0) * (ambient->color.b / 255.0)
		* ambient->lighting_ratio * 255.0;
	return (result);
}
