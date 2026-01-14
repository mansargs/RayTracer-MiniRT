/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:13:51 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/14 16:25:38 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "intersection.h"
#include "ambient.h"
#include "math.h"

t_rgb	compute_ambient(t_hit *hit, t_ambient *ambient)
{
	t_rgb	result;
	t_rgb	surface_color;

	result = (t_rgb){0.0, 0.0, 0.0};
	surface_color = find_surface_color(hit);
	result.r = surface_color.r * ambient->color.r * ambient->lighting_ratio;
	result.g = surface_color.g * ambient->color.g * ambient->lighting_ratio;
	result.b = surface_color.b * ambient->color.b * ambient->lighting_ratio;
	return (result);
}
