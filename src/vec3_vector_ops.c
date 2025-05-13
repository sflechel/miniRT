/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_vector_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:34:09 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/13 10:35:23 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

float	get_magnitude(t_vec3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	vector_normalization(t_vec3 vec)
{
	const float	magnitude = get_magnitude(vec);

	return ((t_vec3){vec.x / magnitude, vec.y / magnitude, vec.z / magnitude});
}

t_vec3	vector_subtraction(t_vec3 minuend, t_vec3 subtrahend)
{
	t_vec3	output;

	output.x = minuend.x - subtrahend.x;
	output.y = minuend.y - subtrahend.y;
	output.z = minuend.z - subtrahend.z;
	return (output);
}

t_vec3	vector_sum(t_vec3 term1, t_vec3 term2)
{
	t_vec3	output;

	output.x = term1.x + term2.x;
	output.y = term1.y + term2.y;
	output.z = term1.z + term2.z;
	return (output);
}
