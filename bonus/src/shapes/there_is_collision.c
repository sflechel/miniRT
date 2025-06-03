/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   there_is_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:19:38 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/03 18:38:11 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	cylinder_collision(const t_cylinder_list *list, const t_ray ray, const t_col cam_col)
{
	const int	same_type = cam_col.type == TYPE_CYLINDER || cam_col.type
		== TYPE_CAP_UP || cam_col.type == TYPE_CAP_DOWN;
	const int	nb_shapes = list->nb_shapes - 1;
	float		col;
	int			i;

	i = -1;
	while (i < nb_shapes)
	{
		i++;
		if (same_type && i == cam_col.index)
			continue ;
		col = cylinder_get_collision(&list->array[i], ray);
		if (col >= 0)
			return (1);
		col = cap_up_get_collision(&list->array[i], ray);
		if (col >= 0)
			return (1);
		col = cap_down_get_collision(&list->array[i], ray);
		if (col >= 0)
			return (1);
	}
	return (0);
}

static int	plane_collision(const t_plane_list *list, const t_ray ray, const t_col cam_col)
{
	const int	same_type = cam_col.type == TYPE_PLANE;
	const int	nb_shapes = list->nb_shapes - 1;
	float		col;
	int			i;

	i = -1;
	while (i < nb_shapes)
	{
		i++;
		if (same_type && i == cam_col.index)
			continue ;
		col = plane_get_collision(&list->array[i], ray);
		if (col >= 0)
			return (1);
	}
	return (0);
}

static int	sphere_collision(const t_sphere_list *list, const t_ray ray, const t_col cam_col)
{
	const int	same_type = cam_col.type == TYPE_SPHERE;
	const int	nb_shapes = list->nb_shapes - 1;
	float		col;
	int			i;

	i = -1;
	while (i < nb_shapes)
	{
		i++;
		if (same_type && i == cam_col.index)
			continue ;
		col = sphere_get_collision(&list->array[i], ray);
		if (col >= 0)
			return (1);
	}
	return (0);
}

static int	hyper_collision(const t_hyper_list *list, const t_ray ray, const t_col cam_col)
{
	const int	same_type = cam_col.type == TYPE_HYPER;
	const int	nb_shapes = list->nb_shapes - 1;
	float		col;
	int			i;

	i = -1;
	while (i < nb_shapes)
	{
		i++;
		if (same_type && i == cam_col.index)
			continue ;
		col = hyper_get_collision(&list->array[i], ray);
		if (col >= 0)
			return (1);
	}
	return (0);
}

int	there_is_collision(const t_data *shapes, const t_ray ray, const t_col cam_col)
{
	if (sphere_collision(shapes->spheres, ray, cam_col) == 1
		|| plane_collision(shapes->planes, ray, cam_col) == 1
		|| cylinder_collision(shapes->cylinders, ray, cam_col) == 1
		|| hyper_collision(shapes->hypers, ray, cam_col) == 1)
	{
		return (1);
	}
	return (0);
}
