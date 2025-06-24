/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:58:39 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/24 11:22:44 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"
#include "shapes.h"
#include <math.h>

void	plane_get_texture(const t_col *restrict col,
			const t_plane *restrict plane, t_color *color, t_color *bump)
{
	int	img_sizes[2];
	int	u_coord;
	int	v_coord;

	get_txtr_or_bump_sizes(plane->txtr, plane->bump, img_sizes);
	u_coord = (int)dot_product(col->pos_world, plane->u) % img_sizes[0];
	v_coord = (int)dot_product(col->pos_world, plane->v) % img_sizes[1];
	if (u_coord < 0)
		u_coord += img_sizes[0];
	if (v_coord < 0)
		v_coord += img_sizes[1];
	if (plane->txtr != 0)
		(*color).rgba = get_color_from_img(plane->txtr, u_coord, v_coord);
	if (plane->bump != 0)
		(*bump).rgba = get_color_from_img(plane->bump, u_coord, v_coord);
}

void	cap_get_texture(const t_col *restrict col,
			const t_cylinder *restrict cylinder, t_color *color, t_color *bump)
{
	t_vec3	u;
	t_vec3	v;
	int		u_coord;
	int		v_coord;
	int		img_sizes[2];

	get_txtr_or_bump_sizes(cylinder->txtr, cylinder->bump, img_sizes);
	u = cross_product(col->normal, (t_vec3){0, 1, 0});
	if (vector_equal(u, (t_vec3){0, 0, 0}) == 1)
		u = cross_product(col->normal, (t_vec3){1, 0, 0});
	v = cross_product(col->normal, u);
	u = scalar_mult(u, TEXTURE_SCALE);
	v = scalar_mult(v, TEXTURE_SCALE);
	u_coord = (int)dot_product(col->pos_world, u) % img_sizes[0];
	v_coord = (int)dot_product(col->pos_world, v) % img_sizes[1];
	if (u_coord < 0)
		u_coord += img_sizes[0];
	if (v_coord < 0)
		v_coord += img_sizes[1];
	if (cylinder->txtr != 0)
		(*color).rgba = get_color_from_img(cylinder->txtr, u_coord, v_coord);
	if (cylinder->bump != 0)
		(*bump).rgba = get_color_from_img(cylinder->bump, u_coord, v_coord);
}

void	sphere_get_texture(const t_col *restrict col,
			const t_sphere *restrict sphere, t_color *color, t_color *bump)
{
	const float	latitude = 0.5 - asinf(col->normal.y) / M_PI;
	const float	longitude = 0.5
		- atan2f(col->normal.z, col->normal.x) / (2 * M_PI);
	int			u_coord;
	int			v_coord;
	int			img_sizes[2];

	get_txtr_or_bump_sizes(sphere->txtr, sphere->bump, img_sizes);
	u_coord = longitude * img_sizes[0];
	v_coord = latitude * img_sizes[1];
	if (sphere->txtr != 0)
		(*color).rgba = get_color_from_img(sphere->txtr, u_coord, v_coord);
	if (sphere->bump != 0)
		(*bump).rgba = get_color_from_img(sphere->bump, u_coord, v_coord);
}

void	cylinder_get_texture(const t_col *restrict col,
			const t_cylinder *restrict cylinder, t_color *color, t_color *bump)
{
	const t_vec3	p = vector_sub(cylinder->pos, col->pos_world);
	const t_vec3	p_proj = ortho_proj(p, cylinder->axis);
	const float		height = dot_product(p, cylinder->axis)
		/ cylinder->height + 0.5;
	const t_vec3	p_perp = vector_sub(p, p_proj);
	t_cylinder_txtr	data;
	int				img_sizes[2];

	get_txtr_or_bump_sizes(cylinder->txtr, cylinder->bump, img_sizes);
	data.azimut = dot_product(p_perp, cylinder->txtr_origin)
		/ (cylinder->radius_squared);
	data.azimut = 0.5 * acosf(data.azimut) / M_PI;
	if (dot_product(p_perp, cylinder->txtr_origin_rot) < 0)
		data.azimut = 1 - data.azimut;
	data.u_coord = data.azimut * cylinder->txtr->width;
	data.v_coord = height * cylinder->txtr->height;
	if (cylinder->txtr != 0)
		(*color).rgba = get_color_from_img(cylinder->txtr,
				data.u_coord, data.v_coord);
	if (cylinder->bump != 0)
		(*bump).rgba = get_color_from_img(cylinder->bump,
				data.u_coord, data.v_coord);
}

void	ellipsoid_get_texture(const t_col *restrict col,
			const t_hyper *restrict hyper, t_color *color, t_color *bump)
{
	const float	latitude = 0.5 - asinf(col->normal.y) / M_PI;
	const float	longitude = 0.5
		- atan2f(col->normal.z, col->normal.x) / (2 * M_PI);
	int			u_coord;
	int			v_coord;
	int			img_sizes[2];

	get_txtr_or_bump_sizes(hyper->txtr, hyper->bump, img_sizes);
	u_coord = longitude * img_sizes[0];
	v_coord = latitude * img_sizes[1];

	if (hyper->txtr != 0)
		(*color).rgba = get_color_from_img(hyper->txtr, u_coord, v_coord);
	if (hyper->bump != 0)
		(*bump).rgba = get_color_from_img(hyper->bump, u_coord, v_coord);
}
