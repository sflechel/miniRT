/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:17 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/03 18:22:38 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shapes.h"

static void	get_collision_color_cylinder_and_cap(t_data *shapes, t_col *col, t_type type)
{
	const t_cylinder	cylinder = shapes->cylinders->array[col->index];

	if (type == TYPE_CYLINDER)
	{
		if (cylinder.txtr != 0)
			col->color = cylinder_get_texture(col, &cylinder);
		else
			col->color = cylinder.color;
	}
	else if (type == TYPE_CAP_UP || type == TYPE_CAP_UP)
	{
		if (cylinder.txtr != 0)
			col->color = cap_get_texture(col, &cylinder);
		else
			col->color = cylinder.color;
	}
}

void	get_collision_color(t_data *shapes, t_col *col)
{
	const t_type	type = col->type;

	if (type == TYPE_PLANE)
	{
		if (shapes->planes->array[col->index].txtr != 0)
			col->color = plane_get_texture(col, &shapes->planes->array[col->index]);
		else
			col->color = shapes->planes->array[col->index].color;
	}
	else if (type == TYPE_SPHERE)
	{
		if (shapes->spheres->array[col->index].txtr != 0)
			col->color = sphere_get_texture(col, &shapes->spheres->array[col->index]);
		else
			col->color = shapes->spheres->array[col->index].color;
	}
	else if (type == TYPE_HYPER)
	{
		if (shapes->hypers->array[col->index].txtr != 0)
			col->color = ellipsoid_get_texture(col, &shapes->hypers->array[col->index]);
		else
			col->color = shapes->hypers->array[col->index].color;
	}
	else
		get_collision_color_cylinder_and_cap(shapes, col, type);
}

