/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:16:59 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/10 10:17:26 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	get_color_from_img(t_image *img, int u_coord, int v_coord)
{
	return (*(int *)(img->addr
		+ (v_coord * img->len_line + u_coord * img->bpp)));
}
