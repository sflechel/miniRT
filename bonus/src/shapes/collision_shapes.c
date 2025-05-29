/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_shapes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:39:23 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/29 15:59:56 by edarnand         ###   ########.fr       */
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

float	hyper_get_collision(t_hyper *hyper, t_ray ray)
{
	const t_vec3	ray_orgigin = vector_sum(ray.origin, hyper->pos); 
	const float	a = dot_product(vector_mult(ray.direction, ray.direction), hyper->param);
	const float	c = -1 + dot_product(vector_mult(ray_orgigin, ray_orgigin), hyper->param);
	const float	h = dot_product(vector_mult(ray_orgigin, ray.direction), hyper->param);
	const float	delta = h * h - a * c;
	float	t;

	if (delta < 0)
        return -1;
	t = (-h - sqrtf(delta)) / a;
	if (t < 0)
		return (-1);
	return (t);
}
