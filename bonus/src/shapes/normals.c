/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:17 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/04 08:19:22 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"
#include "shapes.h"

static t_vec3	cylinder_get_normal(const t_cylinder *cylinder, const t_vec3 col)
{
	const t_vec3	o_col = vector_sub(col, cylinder->pos);
	const t_vec3	o_col_perp = vector_sub(o_col,
			ortho_proj(o_col, cylinder->axis));
	const t_vec3	normal
		= scalar_division(o_col_perp, cylinder->radius);

	return (normal);
}

static t_vec3	sphere_get_normal(const t_sphere *sphere, const t_vec3 col)
{
	t_vec3	normal;

	normal = vector_sub(col, sphere->pos);
	normal = scalar_division(normal, sphere->radius);
	return (normal);
}

static t_vec3	hyper_get_normal(const t_hyper *hyper, const t_vec3 col)
{
	const t_vec3	gradient = quadric_get_gradient(hyper->param);
	const t_vec3	obj_col = matrix_mult_vec3(axis_angle_to_rotation_matrix((t_vec3){0, 1, 0}, hyper->axis), vector_sub(col, hyper->pos));
	t_vec3			normal;

	normal = vector_mult(obj_col, gradient);
	normal = matrix_mult_vec3(axis_angle_to_rotation_matrix(hyper->axis, (t_vec3){0, 1, 0}), normal);
	normal = vector_normalization(normal);
	return (normal);
}

void	get_normal(const t_data *restrict shapes, t_col *restrict col)
{
	if (col->type == TYPE_PLANE)
	{
		col->normal = shapes->planes->array[col->index].normal;
		if (shapes->planes->array[col->index].txtr != 0)
			col->color = plane_get_texture(col, &shapes->planes->array[col->index], shapes->planes->array[col->index].txtr);
		else
			col->color = shapes->planes->array[col->index].color;
	}
	else if (col->type == TYPE_SPHERE)
	{
		col->normal = sphere_get_normal(&shapes->spheres->array[col->index],
				col->pos_world);
		if (shapes->spheres->array[col->index].txtr != 0)
			col->color = sphere_get_texture(col, &shapes->spheres->array[col->index]);
		else
			col->color = shapes->spheres->array[col->index].color;
	}
	else if (col->type == TYPE_CYLINDER)
	{
		col->normal = cylinder_get_normal(
				&shapes->cylinders->array[col->index], col->pos_world);
		if (shapes->cylinders->array[col->index].txtr != 0)
			col->color = cylinder_get_texture(col, &shapes->cylinders->array[col->index]);
		else
			col->color = shapes->cylinders->array[col->index].color;
	}
	else if (col->type == TYPE_CAP_UP)
	{
		col->normal = shapes->cylinders->array[col->index].axis;
		if (shapes->cylinders->array[col->index].txtr != 0)
			col->color = cap_get_texture(col, &shapes->cylinders->array[col->index]);
		else
			col->color = shapes->cylinders->array[col->index].color;
	}
	else if (col->type == TYPE_CAP_DOWN)
	{
		col->normal = scalar_mult(shapes->cylinders->array[col->index].axis, -1);
		if (shapes->cylinders->array[col->index].txtr != 0)
			col->color = cap_get_texture(col, &shapes->cylinders->array[col->index]);
		else
			col->color = shapes->cylinders->array[col->index].color;
	}
	else if (col->type == TYPE_HYPER)
	{
		col->normal = hyper_get_normal(&shapes->hypers->array[col->index], col->pos_world);
		if (shapes->hypers->array[col->index].txtr != 0)
			col->color = ellipsoid_get_texture(col, &shapes->hypers->array[col->index]);
		else
			col->color = shapes->hypers->array[col->index].color;
	}
}
