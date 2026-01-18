/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 01:15:48 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 01:24:02 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phong.h"
#include "minirt.h"

bool	is_in_shadow(t_vec3 point, t_vec3 light_pos, const t_scene *scene)
{
	t_vec3	direction;
	double	distance;
	t_ray	ray;
	t_hit	hit;

	direction = vec_sub(light_pos, point);
	distance = vec_magnitude(direction);
	ray.origin = point;
	ray.direction = vec_normalize(direction);
	hit = objects_intersection(&ray, scene);
	return (hit.is_hit && hit.t < distance);
}
