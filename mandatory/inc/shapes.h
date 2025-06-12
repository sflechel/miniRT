/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:27:04 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/12 08:38:43 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "math_utils.h"

typedef struct s_ray	t_ray;

typedef enum e_type
{
	SPHERE
}	t_type;

typedef struct s_shape	t_shape;

typedef struct s_sphere
{
	float	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	normal;
}	t_plane;

typedef struct s_cylinder
{
	float	radius;
	float	height;
}	t_cylinder;

typedef struct s_disk
{
	float	radius;
	t_vec3	normal;
}	t_disk;

struct s_shape
{
	t_type	type;
	t_vec3	pos;
	t_vec3	axis;
	t_color	color;
	float	(*get_collision)(t_shape *shape, t_ray ray);
	t_vec3	(*get_normal)(t_shape * shape, t_ray * light_ray);
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_disk		disk;
	};
};

typedef struct s_shape_list
{
	int		nb_shapes;
	t_shape	array[];
}	t_shape_list;

typedef struct s_sphere_col
{
	t_vec3	center_vector;
	float	a;
	float	h;
	float	c;
	float	discriminant;
}	t_sphere_col;

typedef struct s_cylinder_col
{
	t_vec3	o_perp;
	t_vec3	d_perp;
	float	a;
	float	h;
	float	c;
	float	discriminant;
	t_vec3	col;
	float	len;
}	t_cylinder_col;

//collision.c
float	get_closest_collision(t_shape_list *shapes, t_ray ray, int *col_index);
int		there_is_collision(t_shape_list *shapes,
			t_ray ray, int curr_shape_index);

//collision_shapes.c
float	disk_get_collision(t_shape *shape, t_ray ray);
float	cylinder_get_collision(t_shape *shape, t_ray ray);
float	sphere_get_collision(t_shape *shape, t_ray ray);
float	plane_get_collision(t_shape *shape, t_ray ray);

//normals.c
t_vec3	disk_get_normal(t_shape *shape, t_ray *light_ray);
t_vec3	cylinder_get_normal(t_shape *shape, t_ray *light_ray);
t_vec3	sphere_get_normal(t_shape *shape, t_ray *light_ray);
t_vec3	plane_get_normal(t_shape *shape, t_ray *light_ray);

#endif
