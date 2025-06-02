/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:39:23 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/02 16:51:08 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"
#include <math.h>

float	sphere_get_collision(const void *sphere_void, const t_ray ray)
{
	const t_sphere	*sphere = (t_sphere*)sphere_void;
	t_sphere_col	data;

	data.origin = vector_sub(sphere->pos, ray.origin);
	data.a = get_squared_norm(ray.direction);
	data.h = dot_product(ray.direction, data.origin);
	data.c = get_squared_norm(data.origin) - (sphere->radius * sphere->radius);
	data.discriminant = data.h * data.h - data.a * data.c;
	if (data.discriminant < 0)
		return (-1);
	data.sqrt_discriminant = sqrtf(data.discriminant);
	data.t = (data.h - data.sqrt_discriminant) / data.a;
	if (data.t > 0)
		return (data.t);
	data.t = (data.h + data.sqrt_discriminant) / data.a;
	if (data.t > 0)
		return (data.t);
	return (-1);
}

float	plane_get_collision(const void *plane_void, const t_ray ray)
{
	const t_plane	*plane = (t_plane*)plane_void;
	const float		dot = dot_product(ray.direction, plane->normal);
	float			intersection;
	t_vec3			origin;

	if (dot == 0)
		return (-1);
	origin = vector_sub(plane->pos, ray.origin);
	intersection = dot_product(origin, plane->normal) / dot;
	if (intersection > 0)
		return (intersection);
	return (-1);
}

float	hyper_get_collision(const void *hyper_void, const t_ray ray)
{
	const t_hyper	*hyper = (t_hyper *)hyper_void;
	t_hyper_col		data;

	data.m = axis_angle_to_rotation_matrix(hyper->axis, (t_vec3){0, 1, 0});
	data.ray_origin = matrix_mult_vec3(data.m,
			vector_sub(ray.origin, hyper->pos));
	data.ray_dir = matrix_mult_vec3(data.m, ray.direction);
	data.a = dot_product(
			vector_mult(data.ray_dir, data.ray_dir), hyper->param);
	data.c = -1 + dot_product(
			vector_mult(data.ray_origin, data.ray_origin), hyper->param);
	data.h = dot_product(
			vector_mult(data.ray_origin, data.ray_dir), hyper->param);
	data.discriminant = data.h * data.h - data.a * data.c;
	if (data.discriminant < 0)
		return (-1);
	data.discriminant_sqrt = sqrtf(data.discriminant);
	data.t = (-data.h - data.discriminant_sqrt) / data.a;
	if (data.t >= 0)
		return (data.t);
	data.t = (-data.h + data.discriminant_sqrt) / data.a;
	if (data.t >= 0)
		return (data.t);
	return (-1);
}
