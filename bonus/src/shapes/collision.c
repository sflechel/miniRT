/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:08:37 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/30 15:18:26 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"
#include "shapes.h"

static void	set_closest(t_col *arr, int nb_col)
{
	int i;

	i = 0;
	while (i < nb_col)
	{
		arr[i].pos = -1;
		i++;
	}
}

int	min_and_greater_0(t_col *col_arr, int nb_col, t_col *closest)
{
	int		i;
	float	dist;

	i = 0;
	dist = -1;
	while (i < nb_col)
	{
		if ((dist > col_arr[i].pos && col_arr[i].pos > 0) || dist == -1)
		{
			dist = col_arr[i].pos;
			*closest = col_arr[i];
		}
		i++;
	}
	if (dist == -1)
		return (1);
	return (0);
}

collision_func get_collision_func(t_type type)
{
	if (type == TYPE_PLANE)
		return (&plane_get_collision);
	if (type == TYPE_SPHERE)
		return (&sphere_get_collision);
	if (type == TYPE_CYLINDER)
		return (&cylinder_get_collision);
	if (type == TYPE_CAP_UP)
		return (&cap_up_get_collision);
	if (type == TYPE_CAP_DOWN)
		return (&cap_down_get_collision);
	if (type == TYPE_HYPER)
		return (&hyper_get_collision);
	return (0);
}

t_col	get_closest_collision_shape(t_cylinder_list *list, t_ray ray, t_type type)
{
	const	collision_func col_func = get_collision_func(type);
	t_col	col;
	float	closest_col;
	float	curr_col;
	int		i;

	closest_col = col_func(&list->array[0], ray);
	col.index = 0;
	col.pos = -1;
	i = 1;
	while (i < list->nb_shapes)
	{
		curr_col = col_func(&list->array[i], ray);
		if (curr_col > 0 && (curr_col < closest_col || closest_col <= 0))
		{
			col.index = i;
			closest_col = curr_col;
		}
		i++;
	}
	if (closest_col <= 0)
		return (col);
	col.pos = closest_col;
	col.type = type;
	return (col);
}

int	get_closest_collision(t_data *shapes, t_ray ray, t_col *col)
{
	t_col	closest[6];
	t_col	closest_shape;

	set_closest(closest, 6);
	if (shapes->planes->nb_shapes > 0)
		closest[0] = get_closest_collision_shape((t_cylinder_list *)shapes->planes, ray, TYPE_PLANE);
	if (shapes->spheres->nb_shapes > 0)
		closest[1] = get_closest_collision_shape((t_cylinder_list *)shapes->spheres, ray, TYPE_SPHERE);
	if (shapes->cylinders->nb_shapes > 0)
	{
		closest[2] = get_closest_collision_shape(shapes->cylinders, ray, TYPE_CYLINDER);
		closest[3] = get_closest_collision_shape(shapes->cylinders, ray, TYPE_CAP_UP);
		closest[4] = get_closest_collision_shape(shapes->cylinders, ray, TYPE_CAP_DOWN);
	}
	if (shapes->hypers->nb_shapes > 0)
		closest[5] = get_closest_collision_shape((t_cylinder_list *)shapes->hypers, ray, TYPE_HYPER);
	if (min_and_greater_0(closest, 6, &closest_shape) == 1)
		return (-1);
	*col = closest_shape;
	col->pos_world = vector_sum(ray.origin,
			scalar_mult(ray.direction, closest_shape.pos));
	get_normal(shapes, col);
	return (closest_shape.pos);
}
