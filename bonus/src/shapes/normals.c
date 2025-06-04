/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:27:17 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/04 14:30:08 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math_utils.h"
#include "shapes.h"

static t_vec3	cylinder_get_normal(const t_cylinder *cylinder, const t_vec3 col)
{
	const t_vec3	o_col = vector_sub(col, cylinder->pos);
	const t_vec3	o_col_perp = vector_sub(o_col,
			ortho_proj(o_col, cylinder->axis));
	const t_vec3	normal
		= scalar_division(o_col_perp, cylinder->radius);

	return (normal);
}

static t_vec3	sphere_get_normal(const t_sphere *sphere, const t_vec3 col)
{
	t_vec3	normal;

	normal = vector_sub(col, sphere->pos);
	normal = scalar_division(normal, sphere->radius);
	return (normal);
}

static t_vec3	hyper_get_normal(const t_hyper *hyper, const t_vec3 col)
{
	const t_vec3	gradient = quadric_get_gradient(hyper->param);
	const t_vec3	obj_col = matrix_mult_vec3(axis_angle_to_rotation_matrix((t_vec3){0, 1, 0}, hyper->axis), vector_sub(col, hyper->pos));
	t_vec3			normal;

	normal = vector_mult(obj_col, gradient);
	normal = matrix_mult_vec3(axis_angle_to_rotation_matrix(hyper->axis, (t_vec3){0, 1, 0}), normal);
	normal = vector_normalization(normal);
	return (normal);
}

void	plane_get_color_and_normal(const t_plane *restrict plane, t_col *restrict col)
{
	t_color	color;
	t_color	bump_color;
	t_vec3	bump_vec;

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

void	cap_up_get_color_and_normal(const t_cylinder *restrict cylinder, t_col *restrict col)
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

void	cap_down_get_color_and_normal(const t_cylinder *restrict cylinder, t_col *restrict col)
{
	t_color	color;
	t_color	bump_color;
	t_vec3	bump_vec;

	col->normal = scalar_mult(cylinder->axis, -1);
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

void	cylinder_get_color_and_normal(const t_cylinder *restrict cylinder, t_col *restrict col)
{
	t_color	color;
	t_color	bump_color;
	t_vec3	bump_vec;

	col->normal = cylinder_get_normal(cylinder, col->pos_world);
	if (cylinder->txtr != 0 || cylinder->bump != 0)
		cylinder_get_texture(col, cylinder, &color, &bump_color);
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

void	sphere_get_color_and_normal(const t_sphere *restrict sphere, t_col *restrict col)
{
	t_color	color;
	t_color	bump_color;
	t_vec3	bump_vec;

	col->normal = sphere_get_normal(sphere, col->pos_world);
	if (sphere->txtr != 0 || sphere->bump != 0)
		sphere_get_texture(col, sphere, &color, &bump_color);
	if (sphere->txtr != 0)
		col->color = color;
	else
		col->color = sphere->color;
	if (sphere->bump != 0)
	{
		bump_vec.x = (float)(bump_color.r - 128) / 128;
		bump_vec.y = (float)(bump_color.g - 128) / 128;
		bump_vec.z = (float)(bump_color.b - 128) / 128;
		bump_vec = scalar_mult(bump_vec, NORMAL_INTENSITY);
		col->normal = vector_sum(col->normal, bump_vec);
		col->normal = vector_normalization(col->normal);
	}
}

void	hyper_get_color_and_normal(const t_hyper *restrict hyper, t_col *restrict col)
{
	t_color	color;
	t_color	bump_color;
	t_vec3	bump_vec;

	col->normal = hyper_get_normal(hyper, col->pos_world);
	if (hyper->txtr != 0 || hyper->bump != 0)
		ellipsoid_get_texture(col, hyper, &color, &bump_color);
	if (hyper->txtr != 0)
		col->color = color;
	else
		col->color = hyper->color;
	if (hyper->bump != 0)
	{
		bump_vec.x = (float)(bump_color.r - 128) / 128;
		bump_vec.y = (float)(bump_color.g - 128) / 128;
		bump_vec.z = (float)(bump_color.b - 128) / 128;
		bump_vec = scalar_mult(bump_vec, NORMAL_INTENSITY);
		col->normal = vector_sum(col->normal, bump_vec);
		col->normal = vector_normalization(col->normal);
	}
}

void	get_color_and_normal(const t_data *restrict shapes, t_col *restrict col)
{
	if (col->type == TYPE_PLANE)
		plane_get_color_and_normal(&shapes->planes->array[col->index], col);
	else if (col->type == TYPE_SPHERE)
		sphere_get_color_and_normal(&shapes->spheres->array[col->index], col);
	else if (col->type == TYPE_CYLINDER)
		cylinder_get_color_and_normal(&shapes->cylinders->array[col->index], col);
	else if (col->type == TYPE_CAP_UP)
		cap_up_get_color_and_normal(&shapes->cylinders->array[col->index], col);
	else if (col->type == TYPE_CAP_DOWN)
		cap_down_get_color_and_normal(&shapes->cylinders->array[col->index], col);
	else if (col->type == TYPE_HYPER)
		hyper_get_color_and_normal(&shapes->hypers->array[col->index], col);
}
