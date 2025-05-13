/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:08:37 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/13 12:38:12 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

float	sphere_get_collision(t_shape *shape, t_ray ray)
{
	const t_vec3	center_vector = vector_subtraction(shape->pos, ray.origin);
	const float		a = get_squared_magnitude(ray.direction);
	const float		h = dot_product(ray.direction, center_vector);
	const float		c = get_squared_magnitude(center_vector) - shape->sphere.radius * shape->sphere.radius;
	const float		discriminant = h * h - a * c;

	if (discriminant < 0)
		return (-1);
	else
		return (h - sqrtf(discriminant) / a);
}
