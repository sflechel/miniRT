/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:39:23 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/11 11:20:19 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"
#include "shapes.h"
#include <math.h>
#include <stdio.h>

float	sphere_get_collision(t_shape *shape, t_ray ray)
{
	t_sphere_col	data;
	float			t;

	data.center_vector = vector_subtraction(shape->pos, ray.origin);
	data.a = get_squared_norm(ray.direction);
	data.h = dot_product(ray.direction, data.center_vector);
	data.c = get_squared_norm(data.center_vector)
		- shape->sphere.radius * shape->sphere.radius;
	data.discriminant = data.h * data.h - data.a * data.c;
	if (data.discriminant < 0)
		return (-1);
	data.discriminant = sqrtf(data.discriminant);
	t = (data.h - data.discriminant) / data.a;
	if (t > 0)
		return (t);
	t = (data.h + data.discriminant) / data.a;
	if (t > 0)
		return (t);
	return (-1);
}

float	cylinder_get_collision(t_shape *shape, t_ray ray)
{
	const t_vec3	o = vector_subtraction(shape->pos, ray.origin);
	t_cylinder_col	col;
	float			t;

	col.d_perp = vector_subtraction(ray.direction,
			ortho_proj(ray.direction, shape->axis));
	col.o_perp = vector_subtraction(o, ortho_proj(o, shape->axis));
	col.a = dot_product(col.d_perp, col.d_perp);
	col.h = dot_product(col.o_perp, col.d_perp);
	col.c = dot_product(col.o_perp, col.o_perp)
		- shape->cylinder.radius * shape->cylinder.radius;
	col.discriminant = col.h * col.h - col.a * col.c;
	if (col.discriminant < 1e-6)
		return (-1);
	col.discriminant = sqrtf(col.discriminant);
	t = (col.h - col.discriminant) / col.a;
	if (t < 1e-6)
		t = (col.h + col.discriminant) / col.a;
	if (t < 1e-6)
		return (-1);
	col.col = vector_sum(ray.origin, scalar_mult(ray.direction, t));
	col.len = dot_product(vector_subtraction(col.col, shape->pos), shape->axis);
	if (fabsf(col.len) < shape->cylinder.height / 2)
		return (t);
	return (-1);
}

float	plane_get_collision(t_shape *shape, t_ray ray)
{
	const float	dot = dot_product(ray.direction, shape->plane.normal);
	float		intersection;
	t_vec3		origin_to_plane;

	if (dot == 0)
		return (-1);
	origin_to_plane = vector_subtraction(shape->pos, ray.origin);
	intersection = dot_product(origin_to_plane, shape->plane.normal) / dot;
	if (intersection > 0)
		return (intersection);
	return (-1);
}

float	disk_get_collision(t_shape *shape, t_ray ray)
{
	const float		dot = dot_product(shape->disk.normal, ray.direction);
	float			intersection;
	t_vec3			origin_to_plane;
	t_vec3			col;

	if (dot == 0)
		return (-1);
	origin_to_plane = vector_subtraction(ray.origin, shape->pos);
	intersection = -dot_product(shape->disk.normal, origin_to_plane) / dot;
	if (intersection < 1e-6)
		return (-1);
	col = vector_sum(origin_to_plane, scalar_mult(ray.direction, intersection));
	if (dot_product(col, col) < shape->disk.radius * shape->disk.radius)
		return (intersection);
	return (-1);
}
