/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:38:41 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/25 01:14:14 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"
# include "window.h"

typedef struct s_hit	t_hit;

typedef void	(*t_checkerboard_fn)(void *, bool);

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

typedef struct s_iter
{
	int	x;
	int	y;
}	t_iter;

void	generate_rays(t_scene *scene, t_window *win);
t_hit	trace_pixel(t_scene *scene, t_window *win, t_iter iter);
t_hit	ray_trace(const t_ray *ray, t_scene *scene, t_window *win, t_iter pos);
t_vec3	ray_at(const t_ray *ray, double t);
void	checkerboard_on_off(t_hit *nearest, int button);
int		get_checker_pattern(const t_hit *hit);

#endif
