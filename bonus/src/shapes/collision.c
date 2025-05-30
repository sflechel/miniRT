/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:08:37 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/30 14:17:57 by edarnand         ###   ########.fr       */
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

int	get_closest_collision(t_data *shapes, t_ray ray, t_col *col)
{
	t_col	closest[6];
	t_col	closest_shape;

	set_closest(closest, 6);
	if (shapes->planes->nb_shapes > 0)
		closest[0] = plane_get_closest_collision(shapes->planes, ray);
	if (shapes->spheres->nb_shapes > 0)
		closest[1] = sphere_get_closest_collision(shapes->spheres, ray);
	if (shapes->cylinders->nb_shapes > 0)
		closest[2] = cylinder_get_closest_collision(shapes->cylinders, ray);
	if (shapes->cylinders->nb_shapes > 0)
		closest[3] = cap_get_closest_collision(shapes->cylinders, ray, TYPE_CAP_UP);
	if (shapes->cylinders->nb_shapes > 0)
		closest[4] = cap_get_closest_collision(shapes->cylinders, ray, TYPE_CAP_DOWN);
	if (shapes->hypers->nb_shapes > 0)
		closest[5] = hyper_get_closest_collision(shapes->hypers, ray);
	if (min_and_greater_0(closest, 6, &closest_shape) == 1)
		return (-1);
	*col = closest_shape;
	col->pos_world = vector_sum(ray.origin,
			scalar_mult(ray.direction, closest_shape.pos));
	get_normal(shapes, col);
	return (closest_shape.pos);
}
