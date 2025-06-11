/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:17 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/11 16:52:10 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	cylinder_get_normal(t_shape *shape, t_ray *light_ray)
{
	const t_vec3	o_col = vector_subtraction(light_ray->origin, shape->pos);
	const t_vec3	o_col_perp = vector_subtraction(o_col,
			ortho_proj(o_col, shape->axis));
	const t_vec3	normal
		= scalar_division(o_col_perp, shape->cylinder.radius);

	return (normal);
}

t_vec3	sphere_get_normal(t_shape *shape, t_ray *light_ray)
{
	t_vec3	normal;

	normal = vector_subtraction(light_ray->origin, shape->pos);
	normal = scalar_division(normal, shape->sphere.radius);
	return (normal);
}

t_vec3	plane_get_normal(t_shape *shape, t_ray *light_ray)
{
	(void)light_ray;
	if (dot_product(light_ray->direction, shape->plane.normal) < 0)
		return (scalar_mult(shape->plane.normal, -1));
	return (shape->plane.normal);
}

t_vec3	disk_get_normal(t_shape *shape, t_ray *light_ray)
{
	(void)light_ray;
	return (shape->disk.normal);
}
