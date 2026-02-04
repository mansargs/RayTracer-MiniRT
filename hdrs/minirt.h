/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 22:36:01 by mansargs          #+#    #+#             */
/*   Updated: 2026/02/04 17:04:32 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_window	t_window;

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct s_vector
{
	void	*data;
	size_t	size;
	size_t	capacity;
	size_t	elem_size;
}	t_vector;

typedef struct s_rgb
{
	double	r;
	double	g;
	double	b;
}	t_rgb;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_specular
{
	double	k_s;
	int		n_s;
}	t_specular;

typedef struct s_loaded_tex
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
	bool	loaded;
}	t_loaded_tex;

typedef struct s_material
{
	t_specular		spec;
	bool			has_specular;
	char			*texture_path;
	char			*bump_map_path;
	t_loaded_tex	color_tex;
	t_loaded_tex	bump_tex;
	void			*mlx;
}	t_material;

typedef struct s_ambient
{
	double	lighting_ratio;
	bool	is_set;
	t_rgb	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	orientation;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	double	fov;
	double	aspect_ratio;
	double	half_height;
	double	half_width;
}	t_camera;

typedef struct s_light
{
	t_vec3	position;
	double	brightness;
	t_rgb	color;
}	t_light;

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
	t_rgb		color;
	bool		checkerboard;
	t_material	mat;
}	t_sphere;

typedef struct s_plane
{
	t_vec3		position;
	t_vec3		orientation;
	t_rgb		color;
	bool		checkerboard;
	t_material	mat;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		orientation;
	double		radius;
	double		height;
	t_rgb		color;
	bool		checkerboard;
	t_material	mat;
}	t_cylinder;

typedef struct s_cone
{
	t_vec3		center;
	t_vec3		orientation;
	double		height;
	double		angle;
	t_rgb		color;
	bool		checkerboard;
	t_material	mat;
}	t_cone;

	typedef enum e_object
	{
		NO_OBJECT = 0,
		SPHERE,
		PLANE,
		CONE,
		CYLINDER
	}			t_object;

typedef struct s_state
{
	int	camera_idx;
}	t_state;

typedef struct s_scene
{
	t_ambient	ambient;
	t_vector	camera;
	t_vector	lights;
	t_vector	spheres;
	t_vector	planes;
	t_vector	cylinders;
	t_vector	cones;
	t_state		state;
	t_window	*win;
	t_camera	*chosen_cam;
}	t_scene;

#endif
