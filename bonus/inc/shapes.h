/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:27:04 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/29 17:18:42 by edarnand         ###   ########.fr       */
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
	float	radius;
	t_vec3	pos;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_image	*txtr;
	t_vec3	pos;
	t_vec3	normal;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_image	*txtr;
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
	int				nb_shapes;
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
	float	a;
	float	h;
	float	c;
	float	discriminant;
}	t_cylinder_col;

//collision.c
int		get_closest_collision(t_data *shapes, t_ray ray, t_col *col);

//there_is_collision
int		there_is_collision(t_data *shapes, t_ray ray, t_col cam_col);

//collision_shapes.c
float	cylinder_get_collision(t_cylinder *cylinder, t_ray ray);
float	sphere_get_collision(t_sphere *sphere, t_ray ray);
float	plane_get_collision(t_plane *plane, t_ray ray);
float	cap_up_get_collision(t_cylinder *cylinder, t_ray ray);
float	cap_down_get_collision(t_cylinder *cylinder, t_ray ray);
float	hyper_get_collision(t_hyper *hyper, t_ray ray);

//collision_shapes_closest.c
t_col	plane_get_closest_collision(t_plane_list *planes, t_ray ray);
t_col	sphere_get_closest_collision(t_sphere_list *spheres, t_ray ray);
t_col	cylinder_get_closest_collision(t_cylinder_list *cylinders, t_ray ray);
t_col	cap_up_get_closest_collision(t_cylinder_list *cylinders, t_ray ray);
t_col	cap_down_get_closest_collision(t_cylinder_list *cylinders, t_ray ray);
t_col	hyper_get_closest_collision(t_hyper_list *hyper, t_ray ray);

//normals.c
void	get_normal(t_data *shapes, t_col *col);
t_vec3	cylinder_get_normal(t_cylinder *shape, t_vec3 col);
t_vec3	sphere_get_normal(t_sphere *shape, t_vec3 col);
t_vec3	hyper_get_normal(t_hyper *shape, t_vec3 col);

//texture.c
t_color	plane_get_texture(const t_col *col, const t_plane *plane);
t_color	sphere_get_texture(const t_col *col, const t_sphere *sphere);
t_color	cylinder_get_texture(const t_col *col, const t_cylinder *cylinder);
t_color	cap_get_texture(const t_col *col, const t_cylinder *cylinder);
t_color	ellipsoid_get_texture(const t_col *col, const t_hyper *hyper);

#endif
