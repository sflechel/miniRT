/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:08:37 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/21 09:36:44 by sflechel         ###   ########.fr       */
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
	float	col_min;
	int		i;

	i = 1;
	col_min = shapes->array[0].get_collision(&shapes->array[0], ray);
	while (i < shapes->nb_shapes)
	{
		col = shapes->array[i].get_collision(&shapes->array[i], ray);
		if (col < 0)
		{
			i++;
			continue ;
		}
		if (col < col_min)
			col_min = col;
		i++;
	}
	if (col_min <= 0)
		return (0);
	return (1);
}

float	sphere_get_collision(t_shape *shape, t_ray ray)
{
	const t_vec3	center_vector = vector_subtraction(shape->pos, ray.origin);
	const float		a = get_squared_norm(ray.direction);
	const float		h = dot_product(ray.direction, center_vector);
	const float		c = get_squared_norm(center_vector) - shape->sphere.radius * shape->sphere.radius;
	const float		discriminant = h * h - a * c;

	if (discriminant < 0)
		return (-1);
	return ((h - sqrtf(discriminant)) / a);
}

float	cylinder_get_collision(t_shape *shape, t_ray ray)
{
	const t_vec3	o = vector_subtraction(shape->pos, ray.origin);
	const t_vec3	d_perp = vector_subtraction(ray.direction,
			ortho_proj(ray.direction, shape->axis));
	const t_vec3	o_perp = vector_subtraction(o, ortho_proj(o, shape->axis));
	const float		a = dot_product(d_perp, d_perp);
	const float		h = dot_product(o_perp, d_perp);
	const float		c = dot_product(o_perp, o_perp) - shape->cylinder.radius * shape->cylinder.radius;
	const float		discriminant = h * h - a * c;
	float			t;
	t_vec3			col;
	float			len;

	if (discriminant < 0)
		return (-1);
	t = (h - sqrtf(discriminant)) / a;
	col = vector_sum(ray.origin, scalar_mult(ray.direction, t));
	len = dot_product(vector_subtraction(col, shape->pos), shape->axis);
	if (len < shape->cylinder.height && len > -shape->cylinder.height)
		return (t);
	return (-1);
}

float	plane_get_collision(t_shape *shape, t_ray ray)
{
	const t_vec3	center_vector = vector_subtraction(shape->pos, ray.origin);
	const float		dot_prod = dot_product(shape->plane.normal, center_vector);
	const float		dot_prod2 = dot_product(shape->plane.normal, ray.direction);
	float			res;

	if (dot_prod2 == 0)
		return (-1);
	res = dot_prod / dot_prod2;
	if (res > 0)
		return (res);
	return (-1);
}

float	disk_get_collision(t_shape *shape, t_ray ray)
{
	const t_vec3	o = vector_subtraction(shape->pos, ray.origin);
	const float		dot_prod = dot_product(shape->disk.normal, o);
	const float		dot_prod2 = dot_product(shape->disk.normal, ray.direction);
	float			t;
	t_vec3			col;

	if (dot_prod2 == 0)
		return (-1);
	t = dot_prod / dot_prod2;
	if (t < 0)
		return (-1);
	col = vector_sum(ray.origin, scalar_mult(ray.direction, t));
	if (dot_product(col, col) < shape->disk.radius * shape->disk.radius)
		return (t);
	return (-1);
}

// float	sphere_get_collision(t_shape *shape, t_ray ray)
// {
// 	const t_vec3	center_vector = vector_subtraction(shape->pos, ray.origin);
// 	const float		a = dot_product(ray.direction, ray.direction);
// 	const float		b = -2 * dot_product(ray.direction, center_vector);
// 	const float		c = dot_product(center_vector, center_vector) - shape->sphere.radius * shape->sphere.radius;
// 	const float		discriminant = b * b - 4 * a * c;
//
// 	if (discriminant < 0)
// 		return (-1);
// 	else
// 		return (-b - sqrtf(discriminant) / 2 * a);
// }
