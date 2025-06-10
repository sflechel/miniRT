/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:08:37 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/09 17:12:13 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"

int	closest_col_form_all_shapes(const t_col *col_arr, const int nb_col, t_col *closest)
{
	int		i;
	float	dist;

	i = 0;
	dist = -1;
	while (i < nb_col)
	{
		if (dist == -1 || (dist > col_arr[i].dist && col_arr[i].dist > EPSILON))
		{
			dist = col_arr[i].dist;
			*closest = col_arr[i];
		}
		i++;
	}
	if (dist == -1)
		return (1);
	return (0);
}

t_collision_func	get_collision_func(const t_type type)
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

t_col	closest_col_shape(const t_cylinder_list *list,
	const t_ray ray, const t_type type)
{
	const t_collision_func	col_func = get_collision_func(type);
	const int				nb_shapes = list->nb_shapes;
	t_col					col;
	float					closest_col;
	float					curr_col;
	int						i;

	closest_col = col_func(&list->array[0], ray);
	col.index = 0;
	col.dist = -1;
	i = 1;
	while (i < nb_shapes)
	{
		curr_col = col_func(&list->array[i], ray);
		if (curr_col != -1 && (curr_col < closest_col || closest_col == -1))
		{
			col.index = i;
			closest_col = curr_col;
		}
		i++;
	}
	if (closest_col == -1)
		return (col);
	col.dist = closest_col;
	col.type = type;
	return (col);
}

static void	get_closest_col_per_shape(t_col *restrict arr,
		const int nb_col, const t_data *restrict list, const t_ray ray)
{
	int	i;

	i = 0;
	while (i < nb_col)
	{
		arr[i].dist = -1;
		i++;
	}
	if (list->planes->nb_shapes > 0)
		arr[0] = closest_col_shape(
				(t_cylinder_list *)list->planes, ray, TYPE_PLANE);
	if (list->spheres->nb_shapes > 0)
		arr[1] = closest_col_shape(
				(t_cylinder_list *)list->spheres, ray, TYPE_SPHERE);
	if (list->cylinders->nb_shapes > 0)
	{
		arr[2] = closest_col_shape(list->cylinders, ray, TYPE_CYLINDER);
		arr[3] = closest_col_shape(list->cylinders, ray, TYPE_CAP_UP);
		arr[4] = closest_col_shape(list->cylinders, ray, TYPE_CAP_DOWN);
	}
	if (list->hypers->nb_shapes > 0)
		arr[5] = closest_col_shape(
				(t_cylinder_list *)list->hypers, ray, TYPE_HYPER);
}

int	get_closest_collision(const t_data *restrict list, const t_ray ray, t_col *restrict col)
{
	t_col	arr[6];
	t_col	closest_shape;

	get_closest_col_per_shape(arr, 6, list, ray);
	if (closest_col_form_all_shapes(arr, 6, &closest_shape) == 1)
		return (1);
	closest_shape.pos_world = vector_sum(ray.origin,
		scalar_mult(ray.direction, closest_shape.dist));
	get_color_and_normal(list, &closest_shape, ray);
	*col = closest_shape;
	return (0);
}
