/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:08:37 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/25 14:36:05 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"

float	get_closest_collision(t_data *shapes, t_ray ray, t_col *col)
{
	t_col_info	current_closest;
	t_col_info	closest_shape;

	current_closest = plane_get_closest_collision(shapes->planes, ray);
	closest_shape = sphere_get_closest_collision(shapes->spheres, ray);
	if (closest_shape.pos > 0 && closest_shape.pos < current_closest.pos)
		current_closest = closest_shape;
	closest_shape = cylinder_get_closest_collision(shapes->cylinders, ray);
	if (closest_shape.pos > 0 && closest_shape.pos < current_closest.pos)
		current_closest = closest_shape;
	closest_shape = cap_up_get_closest_collision(shapes->cylinders, ray);
	if (closest_shape.pos > 0 && closest_shape.pos < current_closest.pos)
		current_closest = closest_shape;
	closest_shape = cap_down_get_closest_collision(shapes->cylinders, ray);
	if (closest_shape.pos > 0 && closest_shape.pos < current_closest.pos)
		current_closest = closest_shape;
	if (current_closest.pos < 0)
		return (-1);
	col->pos_world = vector_sum(ray.origin,
			scalar_mult(ray.direction, current_closest.pos));
	get_normal(shapes, current_closest.type, current_closest.index, col);
	return (current_closest.pos);
}

int	there_is_collision(t_data *shapes, t_ray ray)
{
	float	col;
	int		i;

	i = 0;
	while (i < shapes->planes->nb_shapes)
	{
		col = plane_get_collision(&shapes->planes->array[i], ray);
		if (col >= 0)
			return (1);
		i++;
	}
	while (i < shapes->spheres->nb_shapes)
	{
		col = sphere_get_collision(&shapes->spheres->array[i], ray);
		if (col >= 0)
			return (1);
		i++;
	}
	while (i < shapes->cylinders->nb_shapes)
	{
		col = cylinder_get_collision(&shapes->cylinders->array[i], ray);
		if (col >= 0)
			return (1);
		i++;
	}
	while (i < shapes->cylinders->nb_shapes)
	{
		col = cap_up_get_collision(&shapes->cylinders->array[i], ray);
		if (col >= 0)
			return (1);
		i++;
	}
	while (i < shapes->cylinders->nb_shapes)
	{
		col = cap_down_get_collision(&shapes->cylinders->array[i], ray);
		if (col >= 0)
			return (1);
		i++;
	}
	return (0);
}
