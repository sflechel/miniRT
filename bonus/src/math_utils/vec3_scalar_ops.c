/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scalar_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:36:08 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/02 17:09:04 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

t_vec3	scalar_division(const t_vec3 vec, const float scalar)
{
	return ((t_vec3){vec.x / scalar, vec.y / scalar, vec.z / scalar});
}

t_vec3	scalar_mult(const t_vec3 vec, const float scalar)
{
	return ((t_vec3){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}
