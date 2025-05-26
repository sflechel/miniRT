/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:53 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/26 16:52:56 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

t_color	background_color(t_ray ray)
{
	const t_vec3	unit_direction = vector_normalization(ray.direction);
	const float		lerp = unit_direction.y * 0.5 + 0.5;
	const t_color	white = (t_color){{255, 255, 255, 0}};
	const t_color	blue = (t_color){{255, 178, 126, 0}};
	t_color			background;

	background = color_scaling(white, 1 - lerp);
	background = color_sum(background, color_scaling(blue, lerp));
	return (background);
}

t_color	shading(t_data *shapes, t_col col, t_ray light_ray, t_light light)
{
	float			intensity;
	t_color			ambient;
	t_color			pixel_color;

	if (there_is_collision(shapes, light_ray, col))
		pixel_color = (t_color){{0, 0, 0, 0}};
	else
	{
		light_ray.direction = vector_normalization(light_ray.direction);
		intensity = light.brightness * dot_product(light_ray.direction, col.normal);
		if (intensity < 0)
			pixel_color = (t_color){{0, 0, 0, 0}};
		else
			pixel_color = color_scaling(col.color, intensity);
	}
	ambient = color_mult(col.color, light.ambient);
	pixel_color = color_sum(pixel_color, ambient);
	return (pixel_color);
}

t_color	cast_ray(t_ray ray, t_data *shapes, t_light light)
{
	t_color	pixel_color;
	float	col_ray;
	t_col	col;
	t_ray	light_ray;

	col_ray = get_closest_collision(shapes, ray, &col);
	if (col_ray < 0)
		return (background_color(ray));
	light_ray.origin = col.pos_world;
	light_ray.direction = vector_subtraction(light.pos, light_ray.origin);
	//printf("%d\n", (int)col.type);
	pixel_color = shading(shapes, col, light_ray, light);
	return (pixel_color);
}
