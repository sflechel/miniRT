/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:08:37 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/27 13:57:20 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"
#include "shapes.h"

int	min_and_greater_0(t_col *cols, int nb, t_col *closest)
{
	int		i;
	float	dist;

	i = 0;
	dist = -1;
	while (i < nb)
	{
		if ((dist > cols[i].pos && cols[i].pos > 0) || dist == -1)
		{
			dist = cols[i].pos;
			*closest = cols[i];
		}
		i++;
	}
	if (dist == -1)
		return (1);
	return (0);
}

float	get_closest_collision(t_data *shapes, t_ray ray, t_col *col)
{
	t_col	closest[5];
	t_col	closest_shape;

	closest[0] = plane_get_closest_collision(shapes->planes, ray);
	closest[1] = sphere_get_closest_collision(shapes->spheres, ray);
	closest[2] = cylinder_get_closest_collision(shapes->cylinders, ray);
	closest[3] = cap_up_get_closest_collision(shapes->cylinders, ray);
	closest[4] = cap_down_get_closest_collision(shapes->cylinders, ray);
	if (min_and_greater_0(closest, 5, &closest_shape) == 1)
		return (-1);
	*col = closest_shape;
	col->pos_world = vector_sum(ray.origin,
			scalar_mult(ray.direction, closest_shape.pos));
	get_normal(shapes, col);
	return (closest_shape.pos);
}
