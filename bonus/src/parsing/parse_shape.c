/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:42:19 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/27 13:40:48 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"
#include "libft.h"
#include "shapes.h"
#include <stdio.h>

int	handle_cylinder(char **line, t_cylinder_list *list, t_mlx *mlx)
{
	const int	len = ptr_array_len(line);
	t_cylinder	*cylinder;

	cylinder = &list->array[list->nb_shapes];
	printf("parse the cylinder\n");
	if (verif_len(len, 7) == 1
		|| parse_vector3(line[1], &cylinder->pos) == 1
		|| parse_vector3_normalised(line[2], &cylinder->axis) == 1
		|| parse_float(line[3], &cylinder->radius) == 1
		|| parse_float(line[4], &cylinder->height) == 1
		|| parse_rgba(line[5], &cylinder->color) == 1
		|| parse_file(line[6], &cylinder->txtr, mlx) == 1)
	{
		ft_dprintf(STDERR_FILENO, " in a cylinder\n");
		return (1);
	}
	list->nb_shapes++;
	return (0);
}

int	handle_plane(char **line, t_plane_list *list, t_mlx *mlx)
{
	const int	len = ptr_array_len(line);
	t_plane		*plane;

	plane = &list->array[list->nb_shapes];
	printf("parse the plan\n");
	if (verif_len(len, 5) == 1
		|| parse_vector3(line[1], &plane->pos) == 1
		|| parse_vector3_normalised(line[2], &plane->normal) == 1
		|| parse_rgba(line[3], &plane->color) == 1
		|| parse_file(line[4], &plane->txtr, mlx) == 1)
	{
		ft_dprintf(STDERR_FILENO, " in a plane\n");
		return (1);
	}
	list->nb_shapes++;
	return (0);
}

int	handle_sphere(char **line, t_sphere_list *list, t_mlx *mlx)
{
	const int	len = ptr_array_len(line);
	t_sphere	*sphere;

	sphere = &list->array[list->nb_shapes];
	printf("parse the sphere\n");
	if (verif_len(len, 5) == 1
		|| parse_vector3(line[1], &sphere->pos) == 1
		|| parse_float(line[2], &sphere->radius) == 1
		|| parse_rgba(line[3], &sphere->color) == 1
		|| parse_file(line[4], &sphere->txtr, mlx) == 1)
	{
		ft_dprintf(STDERR_FILENO, " in a sphere\n");
		return (1);
	}
	list->nb_shapes++;
	return (0);
}
