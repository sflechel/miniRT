/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:09:25 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/30 13:40:35 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

t_mat_3x3	matrix_mult(t_mat_3x3 m1, t_mat_3x3 m2)
{
	t_mat_3x3	new;

	new.x.x = m1.x.x * m2.x.x + m1.x.y * m2.y.x + m1.x.z * m2.z.x;
	new.x.y = m1.x.x * m2.x.y + m1.x.y * m2.y.y + m1.x.z * m2.z.y;
	new.x.z = m1.x.x * m2.x.z + m1.x.y * m2.y.z + m1.x.z * m2.z.z;
	new.y.x = m1.y.x * m2.x.x + m1.y.y * m2.y.x + m1.y.z * m2.z.x;
	new.y.y = m1.y.x * m2.x.y + m1.y.y * m2.y.y + m1.y.z * m2.z.y;
	new.y.z = m1.y.x * m2.x.z + m1.y.y * m2.y.z + m1.y.z * m2.z.z;
	new.z.x = m1.z.x * m2.x.x + m1.z.y * m2.y.x + m1.z.z * m2.z.x;
	new.z.y = m1.z.x * m2.x.y + m1.z.y * m2.y.y + m1.z.z * m2.z.y;
	new.z.z = m1.z.x * m2.x.z + m1.z.y * m2.y.z + m1.z.z * m2.z.z;
	return (new);
}

t_vec3	matrix_mult_vec3(t_mat_3x3 m, t_vec3 vec)
{
	t_vec3	new;

	new.x = vec.x * m.x.x + vec.y * m.x.y + vec.z * m.x.z;
	new.y = vec.x * m.y.x + vec.y * m.y.y + vec.z * m.y.z;
	new.z = vec.x * m.z.x + vec.y * m.z.y + vec.z * m.z.z;
	return (new);
}

t_mat_3x3	matrix_transpose(t_mat_3x3 m)
{
	t_mat_3x3	mt;

	mt.x = (t_vec3){m.x.x, m.y.x, m.z.x};
	mt.y = (t_vec3){m.x.y, m.y.y, m.z.y};
	mt.z = (t_vec3){m.x.z, m.y.z, m.z.z};
	return (mt);
}
