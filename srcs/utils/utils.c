/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 02:49:30 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/12 22:59:19 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

int	count_attributes(char **attributes)
{
	int	i;

	i = -1;
	while (attributes[++i]);
	return (i);
}

void	print_error(char *str)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}
