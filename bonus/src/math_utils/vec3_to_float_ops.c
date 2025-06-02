/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_to_float_ops.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:12:34 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/02 17:09:25 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <math.h>

float	dot_product(const t_vec3 vec1, const t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec3	vector_normalization(const t_vec3 vec)
{
	const float	norm = get_norm(vec);

	return ((t_vec3){vec.x / norm, vec.y / norm, vec.z / norm});
}

float	get_squared_norm(const t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float	get_norm(const t_vec3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
