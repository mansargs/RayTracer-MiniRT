/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:18:24 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/10 02:10:23 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# define EXPECTED_EXTENSION ".rt"
# define EXTENSION_LENGTH 3

# include <stdbool.h>

bool	all_spaces(const char *line);
bool	is_valid_arguments(int argc, char *argv[]);

#endif
