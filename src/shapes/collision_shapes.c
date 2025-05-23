/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:39:23 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/23 18:24:14 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

float	sphere_get_collision(t_shape *shape, t_ray ray)
{
	const t_vec3	center_vector = vector_subtraction(shape->pos, ray.origin);
	const float		a = get_squared_norm(ray.direction);
	const float		h = dot_product(ray.direction, center_vector);
	const float		c = get_squared_norm(center_vector)
		- shape->sphere.radius * shape->sphere.radius;
	const float		discriminant = h * h - a * c;

	if (discriminant < 0)
		return (-1);
	return ((h - sqrtf(discriminant)) / a);
}

float	cylinder_get_collision(t_shape *shape, t_ray ray)
{
	const t_vec3	o = vector_subtraction(shape->pos, ray.origin);
	t_cylinder_col	cyl_col;
	float			t;
	t_vec3			col;
	float			len;

	cyl_col.d_perp = vector_subtraction(ray.direction,
			ortho_proj(ray.direction, shape->axis));
	cyl_col.o_perp = vector_subtraction(o, ortho_proj(o, shape->axis));
	cyl_col.a = dot_product(cyl_col.d_perp, cyl_col.d_perp);
	cyl_col.h = dot_product(cyl_col.o_perp, cyl_col.d_perp);
	cyl_col.c = dot_product(cyl_col.o_perp, cyl_col.o_perp)
		- shape->cylinder.radius * shape->cylinder.radius;
	cyl_col.discriminant = cyl_col.h * cyl_col.h - cyl_col.a * cyl_col.c;
	if (cyl_col.discriminant < 0)
		return (-1);
	t = (cyl_col.h - sqrtf(cyl_col.discriminant)) / cyl_col.a;
	col = vector_sum(ray.origin, scalar_mult(ray.direction, t));
	len = dot_product(vector_subtraction(col, shape->pos), shape->axis);
	if (len < shape->cylinder.height / 2 && len > -shape->cylinder.height / 2)
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
	if (intersection < 0)
		return (-1);
	col =
		vector_sum(origin_to_plane, scalar_mult(ray.direction, intersection));
	if (dot_product(col, col) < shape->disk.radius * shape->disk.radius)
		return (intersection);
	return (-1);
}
