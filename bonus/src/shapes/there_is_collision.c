/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   there_is_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:19:38 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/30 16:44:44 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	cylinder_collision(t_cylinder_list *list, t_ray ray, t_col cam_col)
{
	const int	same_type = cam_col.type == TYPE_CYLINDER || cam_col.type
		== TYPE_CAP_UP || cam_col.type == TYPE_CAP_DOWN;
	float		col;
	int			i;

	i = 0;
	while (i < list->nb_shapes)
	{
		if (same_type && i == cam_col.index)
		{
			i++;
			continue ;
		}
		col = cylinder_get_collision(&list->array[i], ray);
		if (col >= 0)
			return (1);
		col = cap_up_get_collision(&list->array[i], ray);
		if (col >= 0)
			return (1);
		col = cap_down_get_collision(&list->array[i], ray);
		if (col >= 0)
			return (1);
		i++;
	}
	return (0);
}

static int	plane_collision(t_plane_list *list, t_ray ray, t_col cam_col)
{
	const int	same_type = cam_col.type == TYPE_PLANE;
	float		col;
	int			i;

	i = 0;
	while (i < list->nb_shapes)
	{
		if (same_type && i == cam_col.index)
		{
			i++;
			continue ;
		}
		col = plane_get_collision(&list->array[i], ray);
		if (col >= 0)
			return (1);
		i++;
	}
	return (0);
}

static int	sphere_collision(t_sphere_list *list, t_ray ray, t_col cam_col)
{
	const int	same_type = cam_col.type == TYPE_SPHERE;
	float		col;
	int			i;

	i = 0;
	while (i < list->nb_shapes)
	{
		if (same_type && i == cam_col.index)
		{
			i++;
			continue ;
		}
		col = sphere_get_collision(&list->array[i], ray);
		if (col >= 0)
			return (1);
		i++;
	}
	return (0);
}

static int	hyper_collision(t_hyper_list *list, t_ray ray, t_col cam_col)
{
	const int	same_type = cam_col.type == TYPE_HYPER;
	float		col;
	int			i;

	i = 0;
	while (i < list->nb_shapes)
	{
		if (same_type && i == cam_col.index)
		{
			i++;
			continue ;
		}
		col = hyper_get_collision(&list->array[i], ray);
		if (col >= 0)
			return (1);
		i++;
	}
	return (0);
}

int	there_is_collision(t_data *shapes, t_ray ray, t_col cam_col)
{
	if (sphere_collision(shapes->spheres, ray, cam_col) == 1)
		return (1);
	if (plane_collision(shapes->planes, ray, cam_col) == 1)
		return (1);
	if (cylinder_collision(shapes->cylinders, ray, cam_col) == 1)
		return (1);
	if (hyper_collision(shapes->hypers, ray, cam_col) == 1)
		return (1);
	return (0);
}
