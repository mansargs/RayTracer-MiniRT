/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 06:48:52 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/10 06:49:49 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	fraction_part(const char *str)
{
	float	fract;
	float	num;

	num = 0.0f;
	fract = 0.1f;
	while (*str >= '0' && *str <= '9')
	{
		num += (*str - '0') * fract;
		fract /= 10.0f;
		str++;
	}
	return num;
}

float	ft_stof(const char *str)
{
	int		sign;
	float	num;

	sign = 1;
	num = 0.0f;
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-' || *str == '+')
		sign = (*str++ == '-') ? -1 : 1;
	while (*str >= '0' && *str <= '9')
		num = 10.0f * num + (*str++ - '0');
	if (*str == '.')
		num += fraction_part(str + 1);
	return num * sign;
}
