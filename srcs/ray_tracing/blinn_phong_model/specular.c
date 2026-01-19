/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:15:42 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 19:47:37 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "vec_math.h"
#include "phong.h"
#include <math.h>

t_rgb compute_specular(const t_light *light, const t_camera *camera,
				const t_hit *hit)
{
	t_vec3				L;
	t_vec3				V;
	t_vec3				H;
	const t_material	*mat;
	double				specular_intensity;

	L = vec_normalize(vec_sub(light->position, hit->point));
	V = vec_normalize(vec_sub(camera->position, hit->point));
	H = vec_normalize(vec_add(L, V));
	mat = find_material(hit);
	if (!mat || mat->spec.k_s == -1 || mat->spec.n_s == -1)
		return (t_rgb){0,0,0};
	specular_intensity = mat->spec.k_s *
							pow(fmax(vec_dot(hit->normal, H), 0.0), mat->spec.n_s);
	return (t_rgb){
		light->color.r * specular_intensity,
		light->color.g * specular_intensity,
		light->color.b * specular_intensity
	};
}
