/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_vector_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:34:09 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/10 10:01:52 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

t_vec3	cross_product(const t_vec3 vec1, const t_vec3 vec2)
{
	t_vec3	output;

	output.x = vec1.y * vec2.z - vec1.z * vec2.y;
	output.y = vec1.z * vec2.x - vec1.x * vec2.z;
	output.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (output);
}

t_vec3	vector_sub(const t_vec3 minuend, const t_vec3 subtrahend)
{
	t_vec3	output;

	output.x = minuend.x - subtrahend.x;
	output.y = minuend.y - subtrahend.y;
	output.z = minuend.z - subtrahend.z;
	return (output);
}

t_vec3	vector_sum(const t_vec3 term1, const t_vec3 term2)
{
	t_vec3	output;

	output.x = term1.x + term2.x;
	output.y = term1.y + term2.y;
	output.z = term1.z + term2.z;
	return (output);
}

t_vec3	vector_mult(const t_vec3 term1, const t_vec3 term2)
{
	t_vec3	output;

	output.x = term1.x * term2.x;
	output.y = term1.y * term2.y;
	output.z = term1.z * term2.z;
	return (output);
}

t_vec3	vector_division(const t_vec3 term1, const t_vec3 term2)
{
	t_vec3	output;

	output.x = term1.x / term2.x;
	output.y = term1.y / term2.y;
	output.z = term1.z / term2.z;
	return (output);
}
