/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:13:01 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/08 17:59:15 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "minirt.h"

void	free_scene(t_scene *scene);
bool	init_scene(t_scene *scene);
void	print_scene(t_scene *scene);

#endif
