/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:15:42 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/22 12:40:28 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "vec_math.h"
#include "phong.h"
#include <math.h>

t_rgb	compute_specular(const t_light *light, const t_camera *camera,
				const t_hit *hit)
{
	t_vec3				l;
	t_vec3				v;
	t_vec3				h;
	const t_material	*mat;
	double				specular_intensity;

	l = vec_normalize(vec_sub(light->position, hit->point));
	v = vec_normalize(vec_sub(camera->position, hit->point));
	h = vec_normalize(vec_add(l, v));
	mat = find_material(hit);
	if (!mat || mat->spec.k_s == -1 || mat->spec.n_s == -1)
		return ((t_rgb){0.0, 0.0, 0.0});
	specular_intensity = mat->spec.k_s
		* pow(fmax(vec_dot(hit->normal, h), 0.0), mat->spec.n_s);
	return ((t_rgb){
		light->color.r * specular_intensity,
		light->color.g * specular_intensity,
		light->color.b * specular_intensity
	});
}
