/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_on_off.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:33:10 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/24 16:05:51 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "intersection.h"
#include <stdio.h>

static void	checker_plane(void *obj, bool enable)
{
	((t_plane *)obj)->checkerboard = enable;
	printf("plane enabled is -> %d\n", enable);
}

static void	checker_sphere(void *obj, bool enable)
{
	((t_sphere *)obj)->checkerboard = enable;
	printf(" sphere enabled is -> %d\n", enable);
}

static void	checker_cylinder(void *obj, bool enable)
{
	((t_cylinder *)obj)->checkerboard = enable;
	printf(" cyl enabled is -> %d\n", enable);
}

static void	checker_cone(void *obj, bool enable)
{
	((t_cone *)obj)->checkerboard = enable;
	printf(" cone enabled is -> %d\n", enable);
}

void	checkerboard_on_off(t_hit *nearest, int button)
{
	bool							enable;
	static const t_checkerboard_fn	checker_fns[] = {
		NULL,
		checker_sphere,
		checker_plane,
		checker_cone,
		checker_cylinder,
	};

	if (!nearest || !nearest->object)
		return ;
	enable = (button == MOUSE_LEFT);
	checker_fns[nearest->type](nearest->object, enable);
}
