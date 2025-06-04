/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:27:04 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/04 14:28:27 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "math_utils.h"

typedef struct s_ray	t_ray;
typedef struct s_data	t_data;
typedef struct s_image	t_image;

typedef enum e_type
{
	TYPE_ERROR,
	TYPE_PLANE,
	TYPE_SPHERE,
	TYPE_CYLINDER,
	TYPE_CAP_UP,
	TYPE_CAP_DOWN,
	TYPE_HYPER,
}	t_type;

typedef struct s_sphere
{
	t_image	*txtr;
	t_image	*bump;
	float	radius;
	t_vec3	pos;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_image	*txtr;
	t_image	*bump;
	t_vec3	pos;
	t_vec3	normal;
	t_vec3	u;
	t_vec3	v;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_image	*txtr;
	t_image	*bump;
	float	radius;
	float	height;
	t_vec3	pos;
	t_vec3	axis;
	t_vec3	txtr_origin;
	t_vec3	txtr_origin_rot;
	t_color	color;
}	t_cylinder;

typedef struct s_hyper
{
	t_image	*txtr;
	t_image	*bump;
	t_vec3	pos;
	t_vec3	param;
	t_vec3	axis;
	t_color	color;
}	t_hyper;

typedef struct s_plane_list
{
	int		nb_shapes;
	t_plane	array[];
}	t_plane_list;

typedef struct s_cylinder_list
{
	int			nb_shapes;
	t_cylinder	array[];
}	t_cylinder_list;

typedef struct s_sphere_list
{
	int			nb_shapes;
	t_sphere	array[];
}	t_sphere_list;

typedef struct s_hyper_list
{
	int		nb_shapes;
	t_hyper	array[];
}	t_hyper_list;

typedef struct s_col
{
	t_vec3	pos_world;
	t_vec3	normal;
	t_color	color;
	t_type	type;
	float	pos;
	int		index;
}	t_col;

typedef struct s_cylinder_col
{
	t_vec3	o_perp;
	t_vec3	d_perp;
	t_vec3	origin;
	t_vec3	col;
	float	a;
	float	h;
	float	c;
	float	len;
	float	discriminant;
	float	discriminant_sqrt;
	float	t;
}	t_cylinder_col;

typedef struct s_cap_col
{
	t_vec3	cap_pos;
	t_vec3	origin;
	t_vec3	col;
	float	dot;
	float	intersection;
}	t_cap_col;

typedef struct s_sphere_col
{
	t_vec3	origin;
	float	a;
	float	h;
	float	c;
	float	discriminant;
	float	sqrt_discriminant;
	float	t;
}	t_sphere_col;

typedef struct s_hyper_col
{
	t_mat_3x3	m;
	t_vec3		ray_origin;
	t_vec3		ray_dir;
	float		a;
	float		c;
	float		h;
	float		discriminant;
	float		discriminant_sqrt;
	float		t;
}	t_hyper_col;

typedef float			(*t_collision_func)(const void *, const t_ray);

//collision.c
int		get_closest_collision(const t_data *list, const t_ray ray, t_col *col);

//there_is_collision
int		there_is_collision(const t_data *shapes, const t_ray ray, const t_col cam_col);

//collision_shapes.c
float	sphere_get_collision(const void *sphere_void, const t_ray ray);
float	plane_get_collision(const void *plane_void, const t_ray ray);
float	hyper_get_collision(const void *hyper_void, const t_ray ray);

//collision_cylinder.c
float	cylinder_get_collision(const void *cylinder_void, const t_ray ray);
float	cap_up_get_collision(const void *cylinder_void, const t_ray ray);
float	cap_down_get_collision(const void *cylinder_void, const t_ray ray);

//normals.c
void	get_color_and_normal(const t_data *restrict shapes, t_col *restrict col);

//texture.c
void	plane_get_texture(const t_col *restrict col, const t_plane *restrict plane, t_color *color, t_color *bump);
void	cap_get_texture(const t_col *restrict col, const t_cylinder *restrict cylinder, t_color *color, t_color *bump);
void	cylinder_get_texture(const t_col *restrict col, const t_cylinder *restrict cylinder, t_color *color, t_color *bump);
void	sphere_get_texture(const t_col *restrict col, const t_sphere *restrict sphere, t_color *color, t_color *bump);
void	ellipsoid_get_texture(const t_col *restrict col, const t_hyper *restrict hyper, t_color *color, t_color *bump);

#endif
