/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:08:37 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/23 15:12:30 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_closest_collision(t_shape_list *shapes, t_ray ray, int *col_index)
{
	float	col;
	float	col_min;
	int		i;

	i = 1;
	*col_index = 0;
	col_min = shapes->array[0].get_collision(&shapes->array[0], ray);
	if (col_min < 0)
		col_min = 0;
	while (i < shapes->nb_shapes)
	{
		col = shapes->array[i].get_collision(&shapes->array[i], ray);
		if (col > 0 && (col < col_min || col_min <= 0))
		{
			col_min = col;
			*col_index = i;
		}
		i++;
	}
	if (col_min <= 0)
		return (-1);
	return (col_min);
}

int	there_is_collision(t_shape_list *shapes, t_ray ray)
{
	float	col;
	int		i;

	i = 1;
	while (i < shapes->nb_shapes)
	{
		col = shapes->array[i].get_collision(&shapes->array[i], ray);
		if (col >= 0)
			return (1);
		i++;
	}
	return (0);
}
