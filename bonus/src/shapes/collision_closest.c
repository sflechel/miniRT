/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:08:37 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/11 11:19:37 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"

int	closest_col_form_all_shapes(const t_col *col_arr,
		const int nb_col, t_col *closest)
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
		arr[0] = closest_col_plane(list->planes, ray);
	if (list->spheres->nb_shapes > 0)
		arr[1] = closest_col_sphere(list->spheres, ray);
	if (list->cylinders->nb_shapes > 0)
	{
		arr[2] = closest_col_cylinder(list->cylinders, ray);
		arr[3] = closest_col_cap_up(list->cylinders, ray);
		arr[4] = closest_col_cap_down(list->cylinders, ray);
	}
	if (list->hypers->nb_shapes > 0)
		arr[5] = closest_col_hyper(list->hypers, ray);
}

int	get_closest_collision(const t_data *restrict list,
		const t_ray ray, t_col *restrict col)
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
