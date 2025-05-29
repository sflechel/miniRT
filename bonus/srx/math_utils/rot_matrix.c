/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:13:05 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/29 15:31:52 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <math.h>

t_mat_3x3	axis_angle_to_rotation_matrix(t_vec3 axis_from, t_vec3 axis_to, float angle)
{
	const float		cosa = dot_product(axis_from, axis_to);
	const t_vec3	a = cross_product(axis_from, axis_to);
	const float		sina = sinf(acosf(cosa));
	const float		ncos = 1 - cosa;
	t_mat_3x3		output;

	output.x.x = ncos * a.x * a.x + cosa;
	output.x.y = ncos * a.x * a.y - a.z * sina;
	output.x.x = ncos * a.x * a.z + a.y * sina;
	output.y.x = ncos * a.x * a.y + a.z * sina;
	output.y.y = ncos * a.y * a.y + cosa;
	output.y.z = ncos * a.y * a.z - a.x * sina;
	output.z.x = ncos * a.x * a.z - a.y * sina;
	output.z.y = ncos * a.y * a.z + a.x * sina;
	output.z.z = ncos * a.z * a.z + cosa;
	return (output);
}

t_mat_3x3	matrix_transpose(t_mat_3x3 m)
{
	t_mat_3x3	mt;

	mt.x = (t_vec3){m.x.x, m.y.x, m.z.x};
	mt.y = (t_vec3){m.x.y, m.y.y, m.z.y};
	mt.z = (t_vec3){m.x.z, m.y.z, m.z.z};
	return (mt);
}
