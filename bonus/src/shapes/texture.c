/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:58:39 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/04 08:21:11 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_color	plane_get_texture(const t_col *restrict col, const t_plane *restrict plane, const t_image *restrict txtr)
{
	int		u_coord;
	int		v_coord;
	t_color	txtr_color;

	u_coord = (int)dot_product(col->pos_world, plane->u) % txtr->width;
	v_coord = (int)dot_product(col->pos_world, plane->v) % txtr->height;
	if (u_coord < 0)
		u_coord += txtr->width;
	if (v_coord < 0)
		v_coord += txtr->height;
	txtr_color.rgba = *((int *)txtr->addr + (v_coord * txtr->len_line + u_coord * txtr->bpp));
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
	txtr_color.rgba = *((int *)cylinder->txtr->addr + (v_coord * cylinder->txtr->len_line + u_coord * cylinder->txtr->bpp));
	return (txtr_color);
}

t_color	sphere_get_texture(const t_col *restrict col, const t_sphere *restrict sphere)
{
	const float	latitude = 0.5 - asinf(col->normal.y) / M_PI;
	const float	longitude = 0.5 - atan2f(col->normal.z, col->normal.x) / (2 * M_PI);
	const int	u_coord = longitude * sphere->txtr->width;
	const int	v_coord = latitude * sphere->txtr->height;
	t_color		txtr_color;

	txtr_color.rgba = *(int *)(sphere->txtr->addr + (v_coord * sphere->txtr->len_line + u_coord * sphere->txtr->bpp));
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
	txtr_color.rgba = *(int *)(cylinder->txtr->addr + (v_coord * cylinder->txtr->len_line + u_coord * cylinder->txtr->bpp));
	return (txtr_color);
}

t_color	ellipsoid_get_texture(const t_col *restrict col, const t_hyper *restrict hyper)
{
	const float	latitude = 0.5 - asinf(col->normal.y) / M_PI;
	const float	longitude = 0.5 - atan2f(col->normal.z, col->normal.x) / (2 * M_PI);
	const int	u_coord = longitude * hyper->txtr->width;
	const int	v_coord = latitude * hyper->txtr->height;
	t_color		txtr_color;

	txtr_color.rgba = *(int *)(hyper->txtr->addr + (v_coord * hyper->txtr->len_line + u_coord * hyper->txtr->bpp));
	return (txtr_color);
}
