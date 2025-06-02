/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_vector_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:34:09 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/30 15:50:36 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

t_vec3	cross_product(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	output;

	output.x = vec1.y * vec2.z - vec1.z * vec2.y;
	output.y = vec1.z * vec2.x - vec1.x * vec2.z;
	output.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (output);
}

t_vec3	ortho_proj(t_vec3 projected, t_vec3 line)
{
	return (scalar_mult(line, dot_product(line, projected)));
}

t_vec3	vector_sub(t_vec3 minuend, t_vec3 subtrahend)
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

t_vec3	vector_division(t_vec3 term1, t_vec3 term2)
{
	t_vec3	output;

	output.x = term1.x / term2.x;
	output.y = term1.y / term2.y;
	output.z = term1.z / term2.z;
	return (output);
}

int	vector_equal(t_vec3 vec1, t_vec3 vec2)
{
	if (vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z)
		return (1);
	return (0);
}
