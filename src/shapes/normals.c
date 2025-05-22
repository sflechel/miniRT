/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:17 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/16 10:17:22 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	cylinder_get_normal(t_shape *shape, t_vec3 col)
{
	const t_vec3	o_col = vector_subtraction(col, shape->pos);
	const t_vec3	o_col_perp = vector_subtraction(o_col,
			ortho_proj(o_col, shape->axis));
	const t_vec3	normal
		= scalar_division(o_col_perp, shape->cylinder.radius);

	return (normal);
}

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

t_vec3	disk_get_normal(t_shape *shape, t_vec3 col)
{
	(void)col;
	return (shape->disk.normal);
}
