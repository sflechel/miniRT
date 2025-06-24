/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:16:59 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/24 11:22:48 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	get_color_from_img(t_image *img, int u_coord, int v_coord)
{
	return (*(int *)(img->addr
		+ (v_coord * img->len_line + u_coord * img->bpp)));
}

void	get_txtr_or_bump_sizes(t_image *txtr, t_image *bump, int *sizes)
{
	if (txtr)
	{
		sizes[0] = txtr->width;
		sizes[1] = txtr->height;
	}
	else
	{
		sizes[0] = bump->width;
		sizes[1] = bump->height;
	}
}
