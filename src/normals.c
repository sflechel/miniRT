/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:17 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/14 16:52:51 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	sphere_get_normal(t_shape *shape, t_vec3 col)
{
	t_vec3	normal;

	normal = vector_subtraction(col, shape->pos);
	normal = scalar_division(normal, shape->sphere.radius);
	return (normal);
}

t_vec3	plane_get_normal(t_shape *shape, t_vec3 col)
{
	(void)col;
	return (shape->plane.normal);
}
