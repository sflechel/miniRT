/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:22:32 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/29 17:31:25 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include "math_utils.h"

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

t_mat_3x3	axis_angle_to_rotation_matrix(t_vec3 axis_from, t_vec3 axis_to)
{
	const float		cosa = dot_product(axis_from, axis_to);
	const t_vec3	a = cross_product(axis_from, axis_to);
	const float		sina = sinf(acosf(cosa));
	const float		ncos = 1 - cosa;
	t_mat_3x3		output;

	output.x.x = ncos * a.x * a.x + cosa;
	output.x.y = ncos * a.x * a.y - a.z * sina;
	output.x.z = ncos * a.x * a.z + a.y * sina;
	output.y.x = ncos * a.x * a.y + a.z * sina;
	output.y.y = ncos * a.y * a.y + cosa;
	output.y.z = ncos * a.y * a.z - a.x * sina;
	output.z.x = ncos * a.x * a.z - a.y * sina;
	output.z.y = ncos * a.y * a.z + a.x * sina;
	output.z.z = ncos * a.z * a.z + cosa;
	return (output);
}
