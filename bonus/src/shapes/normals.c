/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:17 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/25 14:08:42 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "shapes.h"

t_vec3	cylinder_get_normal(t_shape *shape, t_vec3 col)
{
	const t_vec3	o_col = vector_subtraction(col, shape->pos);
	const t_vec3	o_col_perp = vector_subtraction(o_col,
			ortho_proj(o_col, shape->axis));
	const t_vec3	normal
		= scalar_division(o_col_perp, shape->cylinder.radius);

	return (normal);
}

t_vec3	sphere_get_normal(t_shape *shape, t_vec3 col)
{
	t_vec3	normal;

	normal = vector_subtraction(col, shape->pos);
	normal = scalar_division(normal, shape->sphere.radius);
	return (normal);
}

t_col	get_normal(t_data *shapes, t_type type, int i, t_col *col)
{
	if (type == TYPE_PLANE)
	{
		col->normal = shapes->planes->array[i].normal;
		col->color = shapes->planes->array[i].color;
	}
	else if (type == TYPE_SPHERE)
	{
		col->normal = sphere_get_normal(&shapes->spheres->array[i],
				col->pos_world);
		col->color = shapes->spheres->array[i].color;
	}
	else if (type == TYPE_CYLINDER)
	{
		col->normal = cylinder_get_normal(
				&shapes->cylinders->array[i], col->pos_world);
		col->color = shapes->cylinders->array[i].color;
	}
	else if (type == TYPE_CAP_UP)
	{
		col->normal = shapes->cylinders->array[i].axis;
		col->color = shapes->cylinders->array[i].color;
	}
	else if (type == TYPE_CAP_DOWN)
	{
		col->normal = scalar_mult(shapes->cylinders->array[i].axis, -1);
		col->color = shapes->cylinders->array[i].color;
	}
}
