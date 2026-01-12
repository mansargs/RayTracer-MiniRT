/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:28:52 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/12 15:04:02 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "vec_math.h"
#include "ray.h"
#include "minirt.h"

typedef struct s_hit
{
	bool		is_hit;
	t_vec3		point;
	t_vec3		normal;
	double		t;
	t_object	type;
	void		*object;
}			t_hit;

typedef struct s_quad
{
	bool	has_solution;
	double	t1;
	double	t2;
}			t_quad;

typedef struct s_quad_coeffs
{
	double	a;
	double	b;
	double	c;
}			t_quad_coeffs;

t_hit	intersect_sphere(t_ray *ray, t_sphere *sphere);
t_quad	solve_quadratic(t_quad_coeffs coeffs);
double	get_min_positive(double t1, double t2);

#endif
