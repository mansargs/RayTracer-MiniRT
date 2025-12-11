/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 22:36:01 by mansargs          #+#    #+#             */
/*   Updated: 2025/12/11 17:17:48 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_TYPES_H
# define NEW_TYPES_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_vector
{
	void	*data;
	size_t	size;
	size_t	capacity;
	size_t	elem_size;
}	t_vector;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_specular
{
	float	k_s; // 0.0 - 1.0
	int		n_s; // 1 - 128
}	t_specular;

typedef struct s_ambient
{
	float	lighting_ratio;
	bool	is_set;
	t_rgb	color;
}	t_ambient;

typedef struct s_camera
{
	bool	is_set;
	t_vec3	position;
	t_vec3	orientation;
	float	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	position;
	float	brightness;
	t_rgb	color;
}	t_light;

typedef struct s_sphere
{
	t_vec3		center;
	float		diameter;
	t_rgb		color;
	t_specular	specular;
	bool		checkerboard_enabled;
	char		*texture_path;
	char		*bump_map_path;
}	t_sphere;

typedef struct s_plane
{
	t_vec3		position;
	t_vec3		normalized;
	t_rgb		color;
	t_specular	specular;
	bool		checkerboard_enabled;
	char		*texture_path;
	char		*bump_map_path;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		normalized;
	float		diameter;
	float		height;
	t_rgb		color;
	t_specular	specular;
	bool		checkerboard_enabled;
	char		*texture_path;
	char		*bump_map_path;
}	t_cylinder;

typedef struct s_cone
{
	t_vec3		center;
	t_vec3		normalized;
	float		height;
	float		angle;
	t_rgb		color;
	t_specular	specular;
	bool		checkerboard_enabled;
	char		*texture_path;
	char		*bump_map_path;
}	t_cone;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_vector	lights;
	t_vector	spheres;
	t_vector	planes;
	t_vector	cylinders;
	t_vector	cones;
}	t_scene;

#endif
