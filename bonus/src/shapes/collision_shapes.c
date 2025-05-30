/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:39:23 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/30 15:05:30 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"
#include "shapes.h"
#include <math.h>
#include <float.h>

float	sphere_get_collision(void *sphere_void, t_ray ray)
{
	const t_sphere *sphere = (t_sphere*)sphere_void;
	const t_vec3	origin = vector_subtraction(sphere->pos, ray.origin);
	const float		a = get_squared_norm(ray.direction);
	const float		h = dot_product(ray.direction, origin);
	const float		c = get_squared_norm(origin) - (sphere->radius * sphere->radius);
	float			discriminant;
	float			sqrt_discriminant;
	float			t;

	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (-1);
	sqrt_discriminant = sqrtf(discriminant);
	t = (h - sqrt_discriminant) / a;
	if (t > 0)
		return (t);
	t = (h + sqrt_discriminant) / a;
	if (t > 0)
		return (t);
	return (-1);
}

float	plane_get_collision(void *plane_void, t_ray ray)
{
	const t_plane	*plane = (t_plane*)plane_void;
	const float		dot = dot_product(ray.direction, plane->normal);
	float			intersection;
	t_vec3			origin;

	if (dot == 0)
		return (-1);
	origin = vector_subtraction(plane->pos, ray.origin);
	intersection = dot_product(origin, plane->normal) / dot;
	if (intersection > 0)
		return (intersection);
	return (-1);
}

float	cylinder_get_collision(void *cylinder_void, t_ray ray)
{
	const t_cylinder	*cylinder = (t_cylinder*)cylinder_void;
	const t_vec3		origin = vector_subtraction(cylinder->pos, ray.origin);
	t_cylinder_col		cyl_col;
	float				t;
	t_vec3				col;
	float				len;
	float				discriminant_sqrt;

	cyl_col.d_perp = vector_subtraction(ray.direction, ortho_proj(ray.direction, cylinder->axis));
	cyl_col.o_perp = vector_subtraction(origin, ortho_proj(origin, cylinder->axis));
	cyl_col.a = dot_product(cyl_col.d_perp, cyl_col.d_perp);
	cyl_col.h = dot_product(cyl_col.o_perp, cyl_col.d_perp);
	cyl_col.c = dot_product(cyl_col.o_perp, cyl_col.o_perp) - cylinder->radius * cylinder->radius;
	cyl_col.discriminant = cyl_col.h * cyl_col.h - cyl_col.a * cyl_col.c;

	if (cyl_col.discriminant < 0)
		return (-1);
	discriminant_sqrt = sqrtf(cyl_col.discriminant);
	t = (cyl_col.h - discriminant_sqrt) / cyl_col.a;
	if (t < 0)
	{
		t = (cyl_col.h + discriminant_sqrt) / cyl_col.a;
		if (t < 0)
			return (-1);
	}
	col = vector_sum(ray.origin, scalar_mult(ray.direction, t));
	len = dot_product(vector_subtraction(col, cylinder->pos), cylinder->axis);
	if (len < cylinder->height / 2 && len > -cylinder->height / 2)
		return (t);
	return (-1);
}

float	cap_up_get_collision(void *cylinder_void, t_ray ray)
{
	const t_cylinder	*cylinder = (t_cylinder*)cylinder_void;
	const float			dot = dot_product(cylinder->axis, ray.direction);
	float				intersection;
	t_vec3				cap_pos;
	t_vec3				origin;
	t_vec3				col;

	if (dot == 0)
		return (-1);
	cap_pos = vector_sum(cylinder->pos, scalar_mult(cylinder->axis, cylinder->height / 2));
	origin = vector_subtraction(ray.origin, cap_pos);
	intersection = -dot_product(cylinder->axis, origin) / dot;
	if (intersection < 0)
		return (-1);
	col = vector_sum(origin, scalar_mult(ray.direction, intersection));
	if (dot_product(col, col) < cylinder->radius * cylinder->radius)
		return (intersection);
	return (-1);
}

float	cap_down_get_collision(void *cylinder_void, t_ray ray)
{
	const t_cylinder	*cylinder = (t_cylinder*)cylinder_void;
	const float		dot = dot_product(cylinder->axis, ray.direction);
	float			intersection;
	t_vec3			cap_pos;
	t_vec3			origin_to_plane;
	t_vec3			col;

	if (dot == 0)
		return (-1);
	cap_pos = vector_sum(cylinder->pos,
			scalar_mult(cylinder->axis, cylinder->height / -2));
	origin_to_plane = vector_subtraction(ray.origin, cap_pos);
	intersection = -dot_product(cylinder->axis, origin_to_plane) / dot;
	if (intersection < 0)
		return (-1);
	col = vector_sum(origin_to_plane, scalar_mult(ray.direction, intersection));
	if (dot_product(col, col) < cylinder->radius * cylinder->radius)
		return (intersection);
	return (-1);
}

float	hyper_get_collision(void *hyper_void, t_ray ray)
{
	const t_hyper	*hyper = (t_hyper *)hyper_void;
	const t_mat_3x3	m = axis_angle_to_rotation_matrix((t_vec3){0,1,0}, hyper->axis);
	const t_vec3	ray_origin = matrix_mult_vec3( m, vector_subtraction(ray.origin, hyper->pos));
	const t_vec3	ray_dir = matrix_mult_vec3( m, ray.direction);
	const float		a = dot_product(vector_mult(ray_dir, ray_dir), hyper->param);
	const float		c = -1 + dot_product(vector_mult(ray_origin, ray_origin), hyper->param);
	const float		h = dot_product(vector_mult(ray_origin, ray_dir), hyper->param);
	const float		discriminant = h * h - a * c;
	float			discriminant_sqrt;
	float			t;

	if (discriminant < 0)
		return -1;
	discriminant_sqrt = sqrtf(discriminant);
	t = (-h - discriminant_sqrt) / a;
	if (t >= 0)
		return (t);
	t = (-h + discriminant_sqrt) / a;
	if (t >= 0)
		return (t);
	return (-1);
}
