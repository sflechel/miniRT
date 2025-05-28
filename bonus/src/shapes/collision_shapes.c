/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:39:23 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/28 17:00:22 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"
#include "shapes.h"
#include <math.h>

float	sphere_get_collision(t_sphere *sphere, t_ray ray)
{
	const t_vec3	center_vector = vector_subtraction(sphere->pos, ray.origin);
	const float		a = get_squared_norm(ray.direction);
	const float		h = dot_product(ray.direction, center_vector);
	const float		c = get_squared_norm(center_vector)
		- sphere->radius * sphere->radius;
	const float		discriminant = h * h - a * c;

	if (discriminant < 0)
		return (-1);
	return ((h - sqrtf(discriminant)) / a);
}

float	cylinder_get_collision(t_cylinder *cylinder, t_ray ray)
{
	const t_vec3	o = vector_subtraction(cylinder->pos, ray.origin);
	t_cylinder_col	cyl_col;
	float			t;
	t_vec3			col;
	float			len;

	cyl_col.d_perp = vector_subtraction(ray.direction,
			ortho_proj(ray.direction, cylinder->axis));
	cyl_col.o_perp = vector_subtraction(o, ortho_proj(o, cylinder->axis));
	cyl_col.a = dot_product(cyl_col.d_perp, cyl_col.d_perp);
	cyl_col.h = dot_product(cyl_col.o_perp, cyl_col.d_perp);
	cyl_col.c = dot_product(cyl_col.o_perp, cyl_col.o_perp)
		- cylinder->radius * cylinder->radius;
	cyl_col.discriminant = cyl_col.h * cyl_col.h - cyl_col.a * cyl_col.c;
	if (cyl_col.discriminant < 0)
		return (-1);
	t = (cyl_col.h - sqrtf(cyl_col.discriminant)) / cyl_col.a;
	col = vector_sum(ray.origin, scalar_mult(ray.direction, t));
	len = dot_product(vector_subtraction(col, cylinder->pos), cylinder->axis);
	if (len < cylinder->height / 2 && len > -cylinder->height / 2)
		return (t);
	return (-1);
}

float	plane_get_collision(t_plane *plane, t_ray ray)
{
	const float	dot = dot_product(ray.direction, plane->normal);
	float		intersection;
	t_vec3		origin_to_plane;

	if (dot == 0)
		return (-1);
	origin_to_plane = vector_subtraction(plane->pos, ray.origin);
	intersection = dot_product(origin_to_plane, plane->normal) / dot;
	if (intersection > 0)
		return (intersection);
	return (-1);
}

float	cap_up_get_collision(t_cylinder *cylinder, t_ray ray)
{
	const float		dot = dot_product(cylinder->axis, ray.direction);
	float			intersection;
	t_vec3			cap_pos;
	t_vec3			origin_to_plane;
	t_vec3			col;

	if (dot == 0)
		return (-1);
	cap_pos = vector_sum(cylinder->pos,
			scalar_mult(cylinder->axis, cylinder->height / 2));
	origin_to_plane = vector_subtraction(ray.origin, cap_pos);
	intersection = -dot_product(cylinder->axis, origin_to_plane) / dot;
	if (intersection < 0)
		return (-1);
	col = vector_sum(origin_to_plane, scalar_mult(ray.direction, intersection));
	if (dot_product(col, col) < cylinder->radius * cylinder->radius)
		return (intersection);
	return (-1);
}

float	cap_down_get_collision(t_cylinder *cylinder, t_ray ray)
{
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

//float hyper_get_collision(t_hyper *hyper, t_ray ray)
//{
//	float a = 2.0f;
//	float b = 3.0f;
//	float c = 1.5f;

//	hyper->param.x = 1.0f / (a * a);
//	hyper->param.y = 1.0f / (b * b);
//	hyper->param.z = -1.0f / (c * c);

//    const float A = ray.direction.x * ray.direction.x * hyper->param.x
//                  + ray.direction.y * ray.direction.y * hyper->param.y
//                  + ray.direction.z * ray.direction.z * hyper->param.z;

//    const float B = 2.0f * (
//        ray.origin.x * ray.direction.x * hyper->param.x
//      + ray.origin.y * ray.direction.y * hyper->param.y
//      + ray.origin.z * ray.direction.z * hyper->param.z
//    );

//    const float C = ray.origin.x * ray.origin.x * hyper->param.x
//                  + ray.origin.y * ray.origin.y * hyper->param.y
//                  + ray.origin.z * ray.origin.z * hyper->param.z
//                  - 1.0f;

//    const float delta = B * B - 4.0f * A * C;

//    if (delta < 0)
//        return -1;

//    const float sqrt_delta = sqrtf(delta);

//    float t1 = (-B - sqrt_delta) / (2.0f * A);
//    float t2 = (-B + sqrt_delta) / (2.0f * A);

//    // Return smallest positive t
//    if (t1 > 0 && t2 > 0)
//        return fminf(t1, t2);
//    else if (t1 > 0)
//        return t1;
//    else if (t2 > 0)
//        return t2;

//    return -1;
//}


float	hyper_get_collision(t_hyper *hyper, t_ray ray)
{
	float A = 2.0f;
	float B = 3.0f;
	float C = 1.5f;

	hyper->param.x = 1.0f / (A * A);
	hyper->param.y = 1.0f / (B * B);
	hyper->param.z = -1.0f / (C * C);

	const float	a = dot_product(vector_mult(ray.direction, ray.direction), hyper->param);
	const float	c = dot_product(vector_mult(ray.origin, ray.origin), hyper->param) - 1;
	const float	h = dot_product(vector_mult(ray.origin, ray.direction), hyper->param);
	const float	delta = h * h - a * c;
	const float	t = (-h - sqrtf(delta)) / a;

	if (t < 0)
		return (-1);
	return (t);
}
