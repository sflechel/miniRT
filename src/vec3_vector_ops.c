/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_vector_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:34:09 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/21 09:35:44 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

float	dot_product(t_vec3 vec1, t_vec3 vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

float	get_squared_norm(t_vec3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float	get_norm(t_vec3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	ortho_proj(t_vec3 projected, t_vec3 line)
{
	return (scalar_mult(line, dot_product(line, projected)));
}

t_vec3	vector_normalization(t_vec3 vec)
{
	const float	norm = get_norm(vec);

	return ((t_vec3){vec.x / norm, vec.y / norm, vec.z / norm});
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

t_vec3	vector_mult(t_vec3 term1, t_vec3 term2)
{
	t_vec3	output;

	output.x = term1.x * term2.x;
	output.y = term1.y * term2.y;
	output.z = term1.z * term2.z;
	return (output);
}
