/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:17 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/27 11:04:49 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"
#include "shapes.h"

t_vec3	cylinder_get_normal(t_cylinder *cylinder, t_vec3 col)
{
	const t_vec3	o_col = vector_subtraction(col, cylinder->pos);
	const t_vec3	o_col_perp = vector_subtraction(o_col,
			ortho_proj(o_col, cylinder->axis));
	const t_vec3	normal
		= scalar_division(o_col_perp, cylinder->radius);

	return (normal);
}

t_vec3	sphere_get_normal(t_sphere *sphere, t_vec3 col)
{
	t_vec3	normal;

	normal = vector_subtraction(col, sphere->pos);
	normal = scalar_division(normal, sphere->radius);
	return (normal);
}

void	get_normal(t_data *shapes, t_col *col, t_ray ray)
{
	if (col->type == TYPE_PLANE)
	{
		col->normal = shapes->planes->array[i].normal;
		if (shapes->planes->array[i].fd_cmap != -1)
			col->color = plane_get_texture(col, shapes->planes->array[i].fd_cmap);
		else
			col->color = shapes->planes->array[i].color;
	}
	else if (col->type == TYPE_SPHERE)
	{
		col->normal = sphere_get_normal(&shapes->spheres->array[i],
				col->pos_world);
		col->color = shapes->spheres->array[i].color;
	}
	else if (col->type == TYPE_CYLINDER)
	{
		col->normal = cylinder_get_normal(
				&shapes->cylinders->array[i], col->pos_world);
		col->color = shapes->cylinders->array[i].color;
	}
	else if (col->type == TYPE_CAP_UP)
	{
		col->normal = shapes->cylinders->array[i].axis;
		col->color = shapes->cylinders->array[i].color;
	}
	else if (col->type == TYPE_CAP_DOWN)
	{
		col->normal = scalar_mult(shapes->cylinders->array[i].axis, -1);
		col->color = shapes->cylinders->array[i].color;
	}
}
