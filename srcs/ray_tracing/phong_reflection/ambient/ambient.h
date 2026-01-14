/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:33:53 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/14 16:18:28 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_H
# define AMBIENT_H

#include "minirt.h"

typedef t_rgb   (*t_get_color_fn)(void *object);

t_rgb	find_surface_color(const t_hit *hit);

#endif
