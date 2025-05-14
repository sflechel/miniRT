/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scalar_ops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:36:08 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/14 11:03:55 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	scalar_division(t_vec3 vec, float scalar)
{
	return ((t_vec3){vec.x / scalar, vec.y / scalar, vec.z / scalar});
}

t_vec3	scalar_mult(t_vec3 vec, float scalar)
{
	return ((t_vec3){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}
