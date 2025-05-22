/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:08:37 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/22 12:41:25 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

float	get_closest_collision(t_shape_list *shapes, t_ray ray, int *col_index)
{
	float	col;
	float	col_min;
	int		i;

	i = 1;
	*col_index = 0;
	col_min = shapes->array[0].get_collision(&shapes->array[0], ray);
	if (col_min < 0)
		col_min = 0;
	while (i < shapes->nb_shapes)
	{
		col = shapes->array[i].get_collision(&shapes->array[i], ray);
		if (col > 0 && (col < col_min || col_min <= 0))
		{
			col_min = col;
			*col_index = i;
		}
		i++;
	}
	if (col_min <= 0)
		return (-1);
	return (col_min);
}

int	there_is_collision(t_shape_list *shapes, t_ray ray)
{
	float	col;
	int		i;

	i = 1;
	while (i < shapes->nb_shapes)
	{
		col = shapes->array[i].get_collision(&shapes->array[i], ray);
		if (col >= 0)
			return (1);
		i++;
	}
	return (0);
}

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
	cyl_col.c = dot_product(cyl_col.o_perp, cyl_col.o_perp);
	cyl_col.discriminant = dot_product(cyl_col.o_perp, cyl_col.o_perp);
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
	const t_vec3	center_vector = vector_subtraction(shape->pos, ray.origin);
	const float		angle_onorm
		= dot_product(shape->plane.normal, center_vector);
	const float		angle_dirnorm
		= dot_product(shape->plane.normal, ray.direction);
	float			res;

	if (angle_dirnorm == 0)
		return (-1);
	res = angle_onorm / angle_dirnorm;
	if (res > 0)
		return (res);
	return (-1);
}

float	disk_get_collision(t_shape *shape, t_ray ray)
{
	const t_vec3	o = vector_subtraction(ray.origin, shape->pos);
	const float		angle_onorm = dot_product(shape->disk.normal, o);
	const float		angle_dirnorm
		= dot_product(shape->disk.normal, ray.direction);
	float			t;
	t_vec3			col;

	if (angle_dirnorm == 0)
		return (-1);
	t = -angle_onorm / angle_dirnorm;
	if (t < 0)
		return (-1);
	col = vector_sum(o, scalar_mult(ray.direction, t));
	if (dot_product(col, col) < shape->disk.radius * shape->disk.radius)
		return (t);
	return (-1);
}
