/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:42:19 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/22 12:44:55 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdio.h>

static void	handle_disk(t_shape *cylinder, t_shape *disk1, t_shape *disk2)
{
	disk1->get_normal = &disk_get_normal;
	disk1->get_collision = &disk_get_collision;
	disk1->color = cylinder->color;
	disk1->disk.normal = cylinder->axis;
	disk1->disk.radius = cylinder->cylinder.radius;
	disk1->pos = vector_sum(cylinder->pos,
			scalar_mult(cylinder->axis, cylinder->cylinder.height / 2));
	disk2->get_normal = &disk_get_normal;
	disk2->get_collision = &disk_get_collision;
	disk2->color = cylinder->color;
	disk2->disk.normal = scalar_mult(cylinder->axis, -1);
	disk2->disk.radius = cylinder->cylinder.radius;
	disk2->pos = vector_subtraction(cylinder->pos,
			scalar_mult(cylinder->axis, cylinder->cylinder.height / 2));
}

int	handle_cylinder(char **line, t_shape_list *shapes, int index)
{
	const int	len = ptr_array_len(line);
	t_shape		*cylinder;
	t_shape		*disk1;
	t_shape		*disk2;

	cylinder = &shapes->array[index];
	disk1 = &shapes->array[index + 1];
	disk2 = &shapes->array[index + 2];
	printf("parse the cylinder\n");
	if (verif_len(len, 6) == 1
		|| parse_vector3(line[1], &cylinder->pos) == 1
		|| parse_vector3_normalised(line[2], &cylinder->axis) == 1
		|| parse_float(line[3], &cylinder->cylinder.radius) == 1
		|| parse_float(line[4], &cylinder->cylinder.height) == 1
		|| parse_rgba(line[5], &cylinder->color) == 1)
	{
		printf(" in a cylinder\n");
		return (1);
	}
	cylinder->get_collision = &cylinder_get_collision;
	cylinder->get_normal = &cylinder_get_normal;
	handle_disk(cylinder, disk1, disk2);
	return (0);
}

int	handle_plane(char **line, t_shape *plane)
{
	const int	len = ptr_array_len(line);

	printf("parse the plan\n");
	if (verif_len(len, 4) == 1
		|| parse_vector3(line[1], &plane->pos) == 1
		|| parse_vector3_normalised(line[2], &plane->plane.normal) == 1
		|| parse_rgba(line[3], &plane->color) == 1)
	{
		printf(" in a plane\n");
		return (1);
	}
	plane->get_collision = &plane_get_collision;
	plane->get_normal = &plane_get_normal;
	return (0);
}

int	handle_sphere(char **line, t_shape *sphere)
{
	const int	len = ptr_array_len(line);

	printf("parse the sphere\n");
	if (verif_len(len, 4) == 1
		|| parse_vector3(line[1], &sphere->pos) == 1
		|| parse_float(line[2], &sphere->sphere.radius) == 1
		|| parse_rgba(line[3], &sphere->color) == 1)
	{
		printf(" in a sphere\n");
		return (1);
	}
	sphere->get_collision = &sphere_get_collision;
	sphere->get_normal = &sphere_get_normal;
	return (0);
}
