/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:17 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/03 18:24:03 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	cylinder_get_normal(t_cylinder *cylinder, t_vec3 col)
{
	const t_vec3	o_col = vector_sub(col, cylinder->pos);
	const t_vec3	o_col_perp
		= vector_sub(o_col, ortho_proj(o_col, cylinder->axis));
	const t_vec3	normal
		= scalar_division(o_col_perp, cylinder->radius);

	return (normal);
}

static t_vec3	sphere_get_normal(t_sphere *sphere, t_vec3 col)
{
	t_vec3	normal;

	normal = vector_sub(col, sphere->pos);
	normal = scalar_division(normal, sphere->radius);
	return (normal);
}

static t_vec3	hyper_get_normal(t_hyper *hyper, t_vec3 col)
{
	const t_vec3	gradient = quadric_get_gradient(hyper->param);
	const t_mat_3x3	m = axis_angle_to_rotation_matrix((t_vec3){0, 1, 0},
			hyper->axis);
	const t_vec3	obj_col
		= matrix_mult_vec3(m, vector_sub(col, hyper->pos));
	t_vec3			normal;

	normal = vector_mult(obj_col, gradient);
	normal = matrix_mult_vec3(axis_angle_to_rotation_matrix(hyper->axis,
				(t_vec3){0, 1, 0}), normal);
	normal = vector_normalization(normal);
	return (normal);
}

static t_vec3	cap_get_normal(t_cylinder *cylinder, t_type type)
{
	if (type == TYPE_CAP_UP)
		return (cylinder->axis);
	else
		return (scalar_mult(cylinder->axis, -1));
}

void	get_normal(t_data *lists, t_col *col)
{
	if (col->type == TYPE_PLANE)
		col->normal = lists->planes->array[col->index].normal;
	else if (col->type == TYPE_SPHERE)
		col->normal = sphere_get_normal(&lists->spheres->array[col->index],
				col->pos_world);
	else if (col->type == TYPE_HYPER)
		col->normal = hyper_get_normal(
		&lists->hypers->array[col->index], col->pos_world);
	else if (col->type == TYPE_CYLINDER)
		col->normal = cylinder_get_normal(
		&lists->cylinders->array[col->index], col->pos_world);
	else if (col->type == TYPE_CAP_UP)
		col->normal = cap_get_normal(&lists->cylinders->array[col->index], TYPE_CAP_UP);
	else if (col->type == TYPE_CAP_DOWN)
		col->normal = cap_get_normal(&lists->cylinders->array[col->index], TYPE_CAP_DOWN);
}

