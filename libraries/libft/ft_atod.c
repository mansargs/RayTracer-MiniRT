/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 06:48:52 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/19 15:48:52 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	fraction_part(const char *str)
{
	double	fract;
	double	num;

	num = 0.0f;
	fract = 0.1f;
	while (*str >= '0' && *str <= '9')
	{
		num += (*str - '0') * fract;
		fract /= 10.0f;
		str++;
	}
	return (num);
}

double	ft_atod(const char *str)
{
	int		sign;
	double	num;

	sign = 1;
	num = 0.0f;
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		num = 10.0f * num + (*str++ - '0');
	if (*str == '.')
	{
		++str;
		num += fraction_part(str);
	}
	return (num * sign);
}
