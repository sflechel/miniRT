/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:37:00 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/02 17:07:02 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

unsigned char	clamp_uchar(const int c)
{
	if (c <= 0)
		return (0);
	if (c >= 255)
		return (255);
	return (c);
}

t_color	color_mult(const t_color color1, const t_color color2)
{
	t_color	output;

	output.a = color1.a;
	output.r = ((int)color1.r * (int)color2.r) / 255;
	output.g = ((int)color1.g * (int)color2.g) / 255;
	output.b = ((int)color1.b * (int)color2.b) / 255;
	return (output);
}

t_color	color_scaling(const t_color color, const float scale)
{
	t_color	output;

	output.a = color.a;
	output.r = clamp_uchar((int)color.r * scale);
	output.g = clamp_uchar((int)color.g * scale);
	output.b = clamp_uchar((int)color.b * scale);
	return (output);
}

t_color	color_sum(const t_color color1, const t_color color2)
{
	t_color	output;

	output.a = color1.a;
	output.r = clamp_uchar((int)color1.r + (int)color2.r);
	output.g = clamp_uchar((int)color1.g + (int)color2.g);
	output.b = clamp_uchar((int)color1.b + (int)color2.b);
	return (output);
}
