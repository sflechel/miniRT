/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:37:00 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/13 10:37:07 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_scaling(t_color color, float scale)
{
	t_color	output;

	output.a = color.a;
	output.r = color.r * scale;
	output.g = color.g * scale;
	output.b = color.b * scale;
	return (output);
}

t_color	color_sum(t_color color1, t_color color2)
{
	t_color	output;

	output.a = color1.a;
	output.r = color1.r + color2.r;
	output.g = color1.g + color2.g;
	output.b = color1.b + color2.b;
	return (output);
}
