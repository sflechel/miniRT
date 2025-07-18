/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_closest_shapes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:12:54 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/11 11:28:17 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col	closest_col_plane(const t_plane_list *list, const t_ray ray)
{
	const int	nb_shapes = list->nb_shapes;
	t_col		col;
	float		closest_col;
	float		curr_col;
	int			i;

	closest_col = plane_get_collision(&list->array[0], ray);
	col.index = 0;
	col.dist = -1;
	i = 1;
	while (i < nb_shapes)
	{
		curr_col = plane_get_collision(&list->array[i], ray);
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
	col.type = TYPE_PLANE;
	return (col);
}

t_col	closest_col_sphere(const t_sphere_list *list, const t_ray ray)
{
	const int	nb_shapes = list->nb_shapes;
	t_col		col;
	float		closest_col;
	float		curr_col;
	int			i;

	closest_col = sphere_get_collision(&list->array[0], ray);
	col.index = 0;
	col.dist = -1;
	i = 1;
	while (i < nb_shapes)
	{
		curr_col = sphere_get_collision(&list->array[i], ray);
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
	col.type = TYPE_SPHERE;
	return (col);
}

t_col	closest_col_hyper(const t_hyper_list *list, const t_ray ray)
{
	const int	nb_shapes = list->nb_shapes;
	t_col		col;
	float		closest_col;
	float		curr_col;
	int			i;

	closest_col = hyper_get_collision(&list->array[0], ray);
	col.index = 0;
	col.dist = -1;
	i = 1;
	while (i < nb_shapes)
	{
		curr_col = hyper_get_collision(&list->array[i], ray);
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
	col.type = TYPE_HYPER;
	return (col);
}
