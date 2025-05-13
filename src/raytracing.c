/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:53 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/13 15:10:30 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_color	cast_ray(t_ray ray, t_shape_list *shapes, t_light light)
{
	t_color	pixel_color;
	float	col_ray;
	t_vec3	col_world;
	t_vec3	normal;
	t_vec3	light_ray;
	float	intensity;
	float	light_col;

	col_ray = shapes->array[0].get_collision(&shapes->array[0], ray);
	if (col_ray < 0)
		pixel_color = background_color(ray);
	else
	{
		col_world = vector_sum(ray.origin, scalar_multiplication(ray.direction, col_ray));
		normal = vector_subtraction(col_world, shapes->array[0].pos);
		normal = vector_normalization(normal);
		light_ray = vector_subtraction(light.pos, col_world);
		light_col = shapes->array[0].get_collision(&shapes->array[0], (t_ray){col_world, light_ray});
		if (light_col >= 0)
			pixel_color = (t_color){{0, 0, 0, 0}};
		else
		{
			light_ray = vector_normalization(light_ray);
			intensity = light.brightness * dot_product(light_ray, normal);
			if (intensity < 0)
				pixel_color = (t_color){{0, 0, 0, 0}};
			else
				pixel_color = color_scaling(shapes->array[0].color, intensity);
		}
		pixel_color = color_sum(pixel_color, color_scaling(shapes->array[0].color, light.ambient));
	}
	return (pixel_color);
}
