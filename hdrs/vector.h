/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:36:58 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/10 02:13:37 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# define DEFAULT_CAPACITY 4
# define EMPTY_VEC 0
# define GROW 2

# include "new_types.h"
# include <stdbool.h>

bool	vector_init(t_vector *vector, size_t elem_size);
bool	vector_push_back(t_vector *vector, void *elem);
void	vector_free(t_vector *vector);
void	*vector_get(t_vector *vector, size_t index);

#endif
