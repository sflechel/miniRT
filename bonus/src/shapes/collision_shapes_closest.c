/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_shapes_closest.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:13:07 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/26 15:17:04 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_col_info	plane_get_closest_collision(t_plane_list *planes, t_ray ray)
{
	t_col_info	col;
	float		closest_col;
	float		curr_col;
	int			i;

	closest_col = plane_get_collision(&planes->array[0], ray);
	col.index = 0;
	col.pos = -1;
	i = 1;
	while (i < planes->nb_shapes)
	{
		curr_col = plane_get_collision(&planes->array[i], ray);
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
	col.type = TYPE_PLANE;
	return (col);
}

t_col_info	sphere_get_closest_collision(t_sphere_list *spheres, t_ray ray)
{
	t_col_info	col;
	float		closest_col;
	float		curr_col;
	int			i;

	closest_col = sphere_get_collision(&spheres->array[0], ray);
	col.index = 0;
	col.pos = -1;
	i = 1;
	while (i < spheres->nb_shapes)
	{
		curr_col = sphere_get_collision(&spheres->array[i], ray);
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
	col.type = TYPE_SPHERE;
	return (col);
}

t_col_info	cylinder_get_closest_collision(t_cylinder_list *cylinders, t_ray ray)
{
	t_col_info	col;
	float		closest_col;
	float		curr_col;
	int			i;

	closest_col = cylinder_get_collision(&cylinders->array[0], ray);
	col.index = 0;
	col.pos = -1;
	i = 1;
	while (i < cylinders->nb_shapes)
	{
		curr_col = cylinder_get_collision(&cylinders->array[i], ray);
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
	col.type = TYPE_CYLINDER;
	return (col);
}

t_col_info	cap_up_get_closest_collision(t_cylinder_list *cylinders, t_ray ray)
{
	t_col_info	col;
	float		closest_col;
	float		curr_col;
	int			i;

	closest_col = cap_up_get_collision(&cylinders->array[0], ray);
	col.index = 0;
	col.pos = -1;
	i = 1;
	while (i < cylinders->nb_shapes)
	{
		curr_col = cap_up_get_collision(&cylinders->array[i], ray);
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
	col.type = TYPE_CAP_UP;
	return (col);
}

t_col_info	cap_down_get_closest_collision(t_cylinder_list *cylinders, t_ray ray)
{
	t_col_info	col;
	float		closest_col;
	float		curr_col;
	int			i;

	closest_col = cap_down_get_collision(&cylinders->array[0], ray);
	col.index = 0;
	col.pos = -1;
	i = 1;
	while (i < cylinders->nb_shapes)
	{
		curr_col = cap_down_get_collision(&cylinders->array[i], ray);
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
	col.type = TYPE_CAP_DOWN;
	return (col);
}
