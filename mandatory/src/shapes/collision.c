/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:08:37 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/10 08:53:09 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	get_closest_collision(t_shape_list *shapes,
			t_ray ray, int *closest_index)
{
	float	closest_col;
	float	curr_col;
	int		i;

	*closest_index = 0;
	closest_col = shapes->array[0].get_collision(&shapes->array[0], ray);
	i = 1;
	while (i < shapes->nb_shapes)
	{
		curr_col = shapes->array[i].get_collision(&shapes->array[i], ray);
		if (curr_col > 0 && (curr_col < closest_col || closest_col <= 0))
		{
			closest_col = curr_col;
			*closest_index = i;
		}
		i++;
	}
	if (closest_col <= 0)
		return (-1);
	return (closest_col);
}

int	there_is_collision(t_shape_list *shapes, t_ray ray, int curr_shape_index)
{
	float	col;
	int		i;

	i = 0;
	while (i < shapes->nb_shapes)
	{
		if (i != curr_shape_index)
		{
			col = shapes->array[i].get_collision(&shapes->array[i], ray);
			if (col >= 0 && col <= 1)
				return (1);
		}
		i++;
	}
	return (0);
}
