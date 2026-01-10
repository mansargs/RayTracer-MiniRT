/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:38:41 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/10 18:29:35 by mansargs         ###   ########.fr       */
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

void	generate_rays(t_camera *cam, t_window *win);
t_vec3	ray_at(t_ray* ray, double t);

#endif
