/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:27:50 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/04 19:12:27 by mansargs         ###   ########.fr       */
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
#include "get_next_line.h"
#include "mlx.h"
#include "ray.h"
#include "texture.h"

int	main(int argc, char *argv[])
{
	t_scene		scene;
	t_window	window;

	if (!is_valid_arguments(argc, argv))
		return (EXIT_FAILURE);
	if (!init_scene(&scene))
		return (EXIT_FAILURE);
	init_window_params(&window, &scene);
	if (!parse_file(argv[1], &scene))
	{
		free_scene(window.mlx, &scene);
		cleanup_window(&window);
		return (EXIT_FAILURE);
	}
	load_scene(window.mlx, &scene);
	generate_rays(&scene, &window);
	render_image(&window);
	start_loop(&window);
	free_scene(window.mlx, &scene);
	cleanup_window(&window);
	return (EXIT_SUCCESS);
}
