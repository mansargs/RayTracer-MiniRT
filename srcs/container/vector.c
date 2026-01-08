/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 00:39:01 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/08 18:04:41 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"
#include "utils.h"

bool	vector_init(t_vector *vector, size_t elem_size)
{
	if (elem_size == EMPTY_VEC)
		return (false);
	vector->size = EMPTY_VEC;
	vector->capacity = DEFAULT_CAPACITY;
	vector->elem_size = elem_size;
	vector->data = ft_calloc(vector->capacity, elem_size);
	if (!vector->data)
		return (false);
	return (true);
}

void	vector_free(t_vector *vector)
{
	free(vector->data);
	vector->data = NULL;
	vector->size = EMPTY_VEC;
	vector->capacity = EMPTY_VEC;
	vector->elem_size = EMPTY_VEC;
}

void	*vector_get(t_vector *vector, size_t index)
{
	if (index >= vector->size)
		return (NULL);
	return ((void *)((char *)vector->data + index * vector->elem_size));
}

bool	vector_push_back(t_vector *vec, void *elem)
{
	char	*new_data;

	if (vec->size == vec->capacity)
	{
		vec->capacity *= GROW;
		new_data = ft_calloc(vec->capacity, vec->elem_size);
		if (!new_data)
			return (false);
		if (vec->data)
			ft_memcpy(new_data, vec->data, vec->size * vec->elem_size);
		free(vec->data);
		vec->data = new_data;
	}
	ft_memcpy((char *)vec->data + vec->size * vec->elem_size, elem,
		vec->elem_size);
	++vec->size;
	return (true);
}
