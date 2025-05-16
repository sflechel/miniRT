/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:10:11 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/16 11:10:20 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sphere_constructor(t_vec3 pos, t_vec3 axis, t_color color, float radius, t_shape *shape)
{
	shape->pos = pos;
	shape->axis = axis;
	shape->color = color;
	shape->sphere.radius = radius;
	shape->get_collision = &sphere_get_collision;
	shape->get_normal = &sphere_get_normal;
}

void	disk_constructor(t_vec3 pos, t_vec3 axis, t_color color, t_vec3 normal, float radius, t_shape *shape)
{
	shape->pos = pos;
	shape->axis = axis;
	shape->color = color;
	shape->disk.normal = normal;
	shape->disk.radius = radius;
	shape->get_collision = &disk_get_collision;
	shape->get_normal = &disk_get_normal;
}

void	plane_constructor(t_vec3 pos, t_vec3 axis, t_color color, t_vec3 normal, t_shape *shape)
{
	shape->pos = pos;
	shape->axis = axis;
	shape->color = color;
	shape->plane.normal = normal;
	shape->get_collision = &plane_get_collision;
	shape->get_normal = &plane_get_normal;
}

void	cylinder_constructor(t_vec3 pos, t_vec3 axis, t_color color, float radius, float height, t_shape *shape)
{
	shape->pos = pos;
	shape->axis = axis;
	shape->color = color;
	shape->cylinder.radius = radius;
	shape->cylinder.height = height;
	shape->get_collision = &cylinder_get_collision;
	shape->get_normal = &cylinder_get_normal;
}
