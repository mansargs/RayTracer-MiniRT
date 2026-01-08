/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 02:27:50 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/08 18:13:02 by mansargs         ###   ########.fr       */
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

static int init_window_params(t_window* window)
{
	window->mlx = mlx_init();
	if (!window->mlx)
		return (ft_putendl_fd("MLX init failed", STDERR_FILENO), MLX_FAILED);
	window->mlx_window =  mlx_new_window(window->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, WINDOW_NAME);
	if (!window->mlx_window)
		return (ft_putendl_fd("Window opening failed", STDERR_FILENO), MLX_FAILED);
	window->image.img = mlx_new_image(window->mlx, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (!window->image.img)
		return (ft_putendl_fd("Image creating failed", STDERR_FILENO), MLX_FAILED);
	window->image.addr = mlx_get_data_addr(window->image.img,
		&window->image.bits_per_pixel, &window->image.line_length,
		&window->image.endian);
	return (MLX_SUCCESS);
}

static void cleanup_window(t_window* window)
{
	mlx_destroy_image(window->mlx, window->image.img);
	mlx_destroy_window(window->mlx, window->mlx_window);
	mlx_destroy_display(window->mlx);
	free(window->mlx);
}

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
	print_scene(&scene);
	init_window_params(&window);
	sleep(5);
	cleanup_window(&window);
	free_scene(&scene);
	return (EXIT_SUCCESS);
}
