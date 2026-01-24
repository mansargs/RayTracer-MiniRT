/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:28:52 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/24 16:01:16 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "vec_math.h"
# include "ray.h"
# include "minirt.h"

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

typedef struct s_cap
{
	t_vec3	center;
	t_vec3	normal;
	double	radius;
}	t_cap;

typedef struct s_cyl_ctx
{
	const t_ray			*ray;
	const t_cylinder	*cy;
	t_vec3				axis;
}	t_cyl_ctx;

t_hit	objects_intersection(const t_ray *ray, const t_scene *scene);
t_hit	intersect_all_spheres(const t_ray *ray, const t_vector *spheres);
t_hit	intersect_all_planes(const t_ray *ray, const t_vector *planes);
t_hit	intersect_all_cylinders(const t_ray *ray, const t_vector *cylinders);

t_quad	solve_quadratic(t_quad_coeffs coeffs);
double	get_min_positive(double t1, double t2);
double	plane_intersection_formula(const t_ray *ray, t_vec3 plane_p,
			t_vec3 plane_n);
bool	point_in_disk(t_vec3 p, t_vec3 center, double radius, t_vec3 axis);

#endif
