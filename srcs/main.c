/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:27:50 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/10 16:23:22 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "parsing.h"
#include "minirt.h"
#include "vector.h"
#include "libft.h"
#include "utils.h"
#include "window.h"
#include "mlx.h"
#include "ray.h"

int	main(int argc, char *argv[])
{
	t_scene		scene;
	t_window	window;

	if (!is_valid_arguments(argc, argv))
		return (EXIT_FAILURE);
	if (!init_scene(&scene))
		return (EXIT_FAILURE);
	if (!parse_file(argv[1], &scene))
		return (free_scene(&scene), EXIT_FAILURE);
	// print_scene(&scene);
	init_window_params(&window);
	generate_rays(&scene.camera, &window);
	sleep(5);
	cleanup_window(&window);
	free_scene(&scene);
	return (EXIT_SUCCESS);
}
