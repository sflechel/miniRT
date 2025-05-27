/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:58:39 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/27 13:55:53 by sflechel         ###   ########.fr       */
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
	u_coord = dot_product(col->pos_world, u) * plane->txtr->len_line;
	v_coord = dot_product(col->pos_world, v) * plane->txtr->height;
	txtr_color.rgba = *(plane->txtr->addr + (v_coord * plane->txtr->len_line + u_coord));
	return (txtr_color);
}
