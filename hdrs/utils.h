/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 04:41:07 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/12 22:59:31 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "new_types.h"

void	free_split(char **split);
void	free_scene(t_scene *scene);
int		count_attributes(char **attributes);
void	print_error(char *str);

#endif
