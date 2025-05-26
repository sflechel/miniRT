/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:53 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/23 18:01:21 by edarnand         ###   ########.fr       */
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

t_color	shading(t_shape_list *shapes, int shape_index, t_ray light_ray, t_light light)
{
	const t_shape	*shape = &shapes->array[shape_index];
	t_vec3			normal;
	float			intensity;
	t_color			ambient;
	t_color			pixel_color;
	
	if (there_is_collision(shapes, light_ray, shape_index))
		pixel_color = (t_color){{0, 0, 0, 0}};
	else
	{
		normal = shape->get_normal((t_shape *)shape, light_ray.origin);
		light_ray.direction = vector_normalization(light_ray.direction);
		intensity = light.brightness * dot_product(light_ray.direction, normal);
		if (intensity < 0)
			pixel_color = (t_color){{0, 0, 0, 0}};
		else
			pixel_color = color_scaling(shape->color, intensity);
	}
	ambient = color_mult(shape->color, light.ambient);
	pixel_color = color_sum(pixel_color, ambient);
	return (pixel_color);
}

t_color	cast_ray(t_ray ray, t_shape_list *shapes, t_light light)
{
	t_color	pixel_color;
	float	col_ray;
	int		col_index;
	t_ray	light_ray;

	col_ray = get_closest_collision(shapes, ray, &col_index);
	if (col_ray < 0)
		return (background_color(ray));
	light_ray.origin =
		vector_sum(ray.origin, scalar_mult(ray.direction, col_ray));
	light_ray.direction =
		vector_subtraction(light.pos, light_ray.origin);
	pixel_color = shading(shapes, col_index, light_ray, light);
	return (pixel_color);
}
