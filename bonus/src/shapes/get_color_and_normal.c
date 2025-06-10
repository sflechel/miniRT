/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_and_normal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:10:31 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/10 10:12:17 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"
#include "minirt.h"

void	cap_down_get_color_and_normal(const t_cylinder *restrict cylinder,
			t_col *restrict col)
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

void	cylinder_get_color_and_normal(const t_cylinder *restrict cylinder,
			t_col *restrict col)
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

void	sphere_get_color_and_normal(const t_sphere *restrict sphere,
			t_col *restrict col)
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

void	hyper_get_color_and_normal(const t_hyper *restrict hyper,
			t_col *restrict col)
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

void	get_color_and_normal(const t_data *restrict shapes,
			t_col *restrict col, const t_ray ray)
{
	if (col->type == TYPE_PLANE)
		plane_get_color_and_normal(
			&shapes->planes->array[col->index], col, ray);
	else if (col->type == TYPE_SPHERE)
		sphere_get_color_and_normal(&shapes->spheres->array[col->index], col);
	else if (col->type == TYPE_CYLINDER)
		cylinder_get_color_and_normal(
			&shapes->cylinders->array[col->index], col);
	else if (col->type == TYPE_CAP_UP)
		cap_up_get_color_and_normal(&shapes->cylinders->array[col->index], col);
	else if (col->type == TYPE_CAP_DOWN)
		cap_down_get_color_and_normal(
			&shapes->cylinders->array[col->index], col);
	else if (col->type == TYPE_HYPER)
		hyper_get_color_and_normal(&shapes->hypers->array[col->index], col);
}
