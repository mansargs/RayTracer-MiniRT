/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_planes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:36:38 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/15 15:40:20 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../utils/utils.h"
#include "../validation/validation.h"
#include "libft.h"
#include "parsing_internal.h"

static bool	parse_plane_core(char **attr, t_plane *p)
{
    if (!(is_valid_point(attr[1], -INFINITY, INFINITY)
            && is_valid_point(attr[2], -1, 1)
            && is_valid_rgb(attr[3])))
        return (false);
    if (!(parse_point(attr[1], &p->position)
            && parse_point(attr[2], &p->orientation)
            && parse_rgb(attr[3], &p->color)))
        return (false);
    if (!is_normalized_vector(&p->orientation))
        return (print_error("Orientation vector must be normalized"), false);
    return (true);
}

bool	parse_planes(char **attr, t_vector *planes)
{
    t_plane	item;
    size_t	len;

    len = count_attributes(attr);
    if (len < 4)
        return (print_error("Plane attributes count is incorrect"), false);
    if (!parse_plane_core(attr, &item))
        return (false);
    if (!parse_optional_data(attr + 4, &item.mat, len - 4))
        return (false);
    if (!vector_push_back(planes, &item))
        return (print_error("Memory allocation problem"), false);
    return (true);
}
