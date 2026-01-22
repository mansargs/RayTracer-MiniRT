/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:33:53 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/22 13:22:16 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONG_H
# define PHONG_H

# include "minirt.h"
# include "intersection.h"

typedef t_rgb				(*t_get_color_fn)(void *object);
typedef const t_material	*(*t_get_mat_fn)(void *object);

t_rgb				find_surface_color(const t_hit *hit);
const t_material	*find_material(const t_hit *hit);
bool				is_in_shadow(t_vec3 point, t_vec3 light_pos,
						const t_scene *scene);
t_rgb				diffuse_color(const t_light *light, const t_hit *hit);
t_rgb				compute_ambient(const t_hit *hit, const t_ambient *ambient);
t_rgb				compute_specular(const t_light *light,
						const t_camera *camera, const t_hit *hit);
t_rgb				compute_final_color(const t_hit *hit, const t_scene *scene);
int					rgb_to_int(int r, int g, int b);

#endif
