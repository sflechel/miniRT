/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:17 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/30 16:38:04 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	cylinder_get_normal(t_cylinder *cylinder, t_vec3 col)
{
	const t_vec3	o_col = vector_sub(col, cylinder->pos);
	const t_vec3	o_col_perp = vector_sub(o_col,
			ortho_proj(o_col, cylinder->axis));
	const t_vec3	normal
		= scalar_division(o_col_perp, cylinder->radius);

	return (normal);
}

t_vec3	sphere_get_normal(t_sphere *sphere, t_vec3 col)
{
	t_vec3	normal;

	normal = vector_sub(col, sphere->pos);
	normal = scalar_division(normal, sphere->radius);
	return (normal);
}

t_vec3	hyper_get_normal(t_hyper *hyper, t_vec3 col)
{
	const t_vec3	gradient = quadric_get_gradient(hyper->param);
	const t_vec3	normal = vector_normalization(vector_mult(col, gradient));

	return (normal);
}

void	get_normal(t_data *shapes, t_col *col)
{
	if (col->type == TYPE_PLANE)
	{
		col->normal = shapes->planes->array[col->index].normal;
		if (shapes->planes->array[col->index].txtr != 0)
			col->color = plane_get_texture(col, &shapes->planes->array[col->index]);
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
