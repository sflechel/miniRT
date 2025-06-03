/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:58:39 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/03 18:37:26 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_color	plane_get_texture(const t_col *restrict col, const t_plane *restrict plane)
{
	t_vec3	u;
	t_vec3	v;
	int		u_coord;
	int		v_coord;
	t_color	txtr_color;

	u = cross_product(plane->normal, (t_vec3){0, 1, 0});
	if (vector_equal(u, (t_vec3){0, 0, 0}) == 1)
		u = cross_product(plane->normal, (t_vec3){1, 0, 0});
	v = cross_product(plane->normal, u);
	u = scalar_mult(u, 32);
	v = scalar_mult(v, 32);
	u_coord = (int)dot_product(col->pos_world, u) % plane->txtr->width / 4;
	v_coord = (int)dot_product(col->pos_world, v) % plane->txtr->height / 4;
	if (u_coord < 0)
		u_coord += plane->txtr->width / 4;
	if (v_coord < 0)
		v_coord += plane->txtr->height / 4;
	txtr_color.rgba = *((int *)plane->txtr->addr + (v_coord * plane->txtr->len_line + u_coord * plane->txtr->bpp / 8));
	return (txtr_color);
}

t_color	cap_get_texture(const t_col *restrict col, const t_cylinder *restrict cylinder)
{
	t_vec3	u;
	t_vec3	v;
	int		u_coord;
	int		v_coord;
	t_color	txtr_color;

	u = cross_product(col->normal, (t_vec3){0, 1, 0});
	if (vector_equal(u, (t_vec3){0, 0, 0}) == 1)
		u = cross_product(col->normal, (t_vec3){1, 0, 0});
	v = cross_product(col->normal, u);
	u = scalar_mult(u, 64);
	v = scalar_mult(v, 64);
	u_coord = (int)dot_product(col->pos_world, u) % cylinder->txtr->width / 4;
	v_coord = (int)dot_product(col->pos_world, v) % cylinder->txtr->height / 4;
	if (u_coord < 0)
		u_coord += cylinder->txtr->width / 4;
	if (v_coord < 0)
		v_coord += cylinder->txtr->height / 4;
	txtr_color.rgba = *((int *)cylinder->txtr->addr + (v_coord * cylinder->txtr->len_line + u_coord * cylinder->txtr->bpp / 8));
	return (txtr_color);
}

t_color	sphere_get_texture(const t_col *restrict col, const t_sphere *restrict sphere)
{
	const float	latitude = 0.5 - asinf(col->normal.y) / M_PI;
	const float	longitude = 0.5 - atan2f(col->normal.z, col->normal.x) / (2 * M_PI);
	const int	u_coord = longitude * sphere->txtr->width;
	const int	v_coord = latitude * sphere->txtr->height;
	t_color		txtr_color;

	txtr_color.rgba = *(int *)(sphere->txtr->addr + (v_coord * sphere->txtr->len_line + u_coord * sphere->txtr->bpp / 8));
	return (txtr_color);
}

t_color	cylinder_get_texture(const t_col *restrict col, const t_cylinder *restrict cylinder)
{
	const t_vec3	p = vector_sub(cylinder->pos, col->pos_world);
	const t_vec3	p_proj = ortho_proj(p, cylinder->axis);
	const float		height = dot_product(p, cylinder->axis) / cylinder->height + 0.5;
	const t_vec3	p_perp = vector_sub(p, p_proj);
	float			azimut;
	int				u_coord;
	int				v_coord;
	t_color			txtr_color;

	azimut = dot_product(p_perp, cylinder->txtr_origin) / (cylinder->radius * cylinder->radius);
	azimut = 0.5 * acosf(azimut) / M_PI;
	if (dot_product(p_perp, cylinder->txtr_origin_rot) < 0)
		azimut = 1 - azimut;
	u_coord = azimut * cylinder->txtr->width;
	v_coord = height * cylinder->txtr->height;
	txtr_color.rgba = *(int *)(cylinder->txtr->addr + (v_coord * cylinder->txtr->len_line + u_coord * cylinder->txtr->bpp / 8));
	return (txtr_color);
}

t_color	ellipsoid_get_texture(const t_col *restrict col, const t_hyper *restrict hyper)
{
	const float	latitude = 0.5 - asinf(col->normal.y) / M_PI;
	const float	longitude = 0.5 - atan2f(col->normal.z, col->normal.x) / (2 * M_PI);
	const int	u_coord = longitude * hyper->txtr->width;
	const int	v_coord = latitude * hyper->txtr->height;
	t_color		txtr_color;

	txtr_color.rgba = *(int *)(hyper->txtr->addr + (v_coord * hyper->txtr->len_line + u_coord * hyper->txtr->bpp / 8));
	return (txtr_color);
}
