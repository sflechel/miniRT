/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:58:39 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/27 17:48:14 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "shapes.h"
#include "minirt.h"

t_color	plane_get_texture(const t_col *col, const t_plane *plane)
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
	u_coord = (int)dot_product(col->pos_world, u) % plane->txtr->width / 4;
	v_coord = (int)dot_product(col->pos_world, v) % plane->txtr->height / 4;
	if (u_coord < 0)
		u_coord += plane->txtr->width / 4;
	if (v_coord < 0)
		v_coord += plane->txtr->height / 4;
	txtr_color.rgba = *((unsigned int *)plane->txtr->addr + (v_coord * plane->txtr->len_line + u_coord * plane->txtr->bpp / 8));
	return (txtr_color);
}
