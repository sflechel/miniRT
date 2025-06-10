/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:17 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/10 10:14:23 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"
#include "shapes.h"

t_vec3	cylinder_get_normal(const t_cylinder *cylinder,
					const t_vec3 col)
{
	const t_vec3	o_col = vector_sub(col, cylinder->pos);
	const t_vec3	o_col_perp = vector_sub(o_col,
			ortho_proj(o_col, cylinder->axis));
	const t_vec3	normal
		= scalar_division(o_col_perp, cylinder->radius);

	return (normal);
}

t_vec3	sphere_get_normal(const t_sphere *sphere, const t_vec3 col)
{
	t_vec3	normal;

	normal = vector_sub(col, sphere->pos);
	normal = scalar_division(normal, sphere->radius);
	return (normal);
}

t_vec3	hyper_get_normal(const t_hyper *hyper, const t_vec3 col)
{
	const t_vec3	gradient = quadric_get_gradient(hyper->param);
	const t_vec3	obj_col = matrix_mult_vec3(hyper->m_rot_invert,
			vector_sub(col, hyper->pos));
	t_vec3			normal;

	normal = vector_mult(obj_col, gradient);
	normal = matrix_mult_vec3(hyper->m_rot, normal);
	normal = vector_normalization(normal);
	return (normal);
}

void	plane_get_color_and_normal(const t_plane *restrict plane,
			t_col *restrict col, const t_ray ray)
{
	t_color	color;
	t_color	bump_color;
	t_vec3	bump_vec;

	if (dot_product(ray.direction, plane->normal) > 0)
		col->normal = scalar_mult(plane->normal, -1);
	else
		col->normal = plane->normal;
	if (plane->txtr != 0 || plane->bump != 0)
		plane_get_texture(col, plane, &color, &bump_color);
	if (plane->txtr != 0)
		col->color = color;
	else
		col->color = plane->color;
	if (plane->bump != 0)
	{
		bump_vec.x = (float)(bump_color.r - 128) / 128;
		bump_vec.y = (float)(bump_color.g - 128) / 128;
		bump_vec.z = (float)(bump_color.b - 128) / 128;
		bump_vec = scalar_mult(bump_vec, NORMAL_INTENSITY);
		col->normal = vector_sum(col->normal, bump_vec);
		col->normal = vector_normalization(col->normal);
	}
}

void	cap_up_get_color_and_normal(const t_cylinder *restrict cylinder,
			t_col *restrict col)
{
	t_color	color;
	t_color	bump_color;
	t_vec3	bump_vec;

	col->normal = cylinder->axis;
	if (cylinder->txtr != 0 || cylinder->bump != 0)
		cap_get_texture(col, cylinder, &color, &bump_color);
	if (cylinder->txtr != 0)
		col->color = color;
	else
		col->color = cylinder->color;
	if (cylinder->bump != 0)
	{
		bump_vec.x = (float)(bump_color.r - 128) / 128;
		bump_vec.y = (float)(bump_color.g - 128) / 128;
		bump_vec.z = (float)(bump_color.b - 128) / 128;
		bump_vec = scalar_mult(bump_vec, NORMAL_INTENSITY);
		col->normal = vector_sum(col->normal, bump_vec);
		col->normal = vector_normalization(col->normal);
	}
}
