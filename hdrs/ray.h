/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noavetis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:38:41 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/16 23:13:01 by noavetis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"
# include "window.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}			t_ray;

typedef struct s_camera_pixel
{
	double	px;
	double	py;
}			t_camera_pixel;

void	generate_rays(t_scene *scene, t_window *win);
void	ray_trace(const t_ray *ray, t_scene *scene, t_window *win, int x, int y);
t_vec3	ray_at(const t_ray *ray, double t);

#endif
