/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:17 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/13 16:29:16 by sflechel         ###   ########.fr       */
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
