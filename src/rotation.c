/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:22:32 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/14 10:47:08 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	rotation(t_vec3 *vec, t_vec3 rot)
{
	rotation_x(vec, rot.x);
	rotation_y(vec, rot.y);
	rotation_z(vec, rot.z);
}

void	rotation_x(t_vec3 *vec, float angle)
{
	float	cos_a;
	float	sin_a;
	float	buf_y;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	buf_y = vec->y;
	vec->y = cos_a * buf_y - sin_a * vec->z;
	vec->z = sin_a * buf_y + cos_a * vec->z;
}

void	rotation_y(t_vec3 *vec, float angle)
{
	float	cos_a;
	float	sin_a;
	float	buf_x;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	buf_x = vec->x;
	vec->x = cos_a * buf_x + sin_a * vec->z;
	vec->z = cos_a * vec->z - sin_a * buf_x;
}

void	rotation_z(t_vec3 *vec, float angle)
{
	float	cos_a;
	float	sin_a;
	float	buf_x;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	buf_x = vec->x;
	vec->x = cos_a * buf_x - sin_a * vec->y;
	vec->y = sin_a * buf_x + cos_a * vec->y;
}
