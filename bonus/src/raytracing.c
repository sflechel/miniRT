/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:53 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/10 09:10:39 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"
#include "shapes.h"

t_color	background_color(const t_ray ray)
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

t_vec3	get_light_ray_reflected(const t_col col, const t_ray light_ray)
{
	const t_vec3	reflect_proj = ortho_proj(light_ray.direction, col.normal);
	const t_vec3	mult_by_2 = scalar_mult(reflect_proj, 2);
	const t_vec3	reflected = vector_sub(mult_by_2, light_ray.direction);

	return (reflected);
}

t_color	calc_specular(const t_col col, const t_ray light_ray)
{
	const t_vec3	reflected = get_light_ray_reflected(col, light_ray);
	const float		specular_constant = 0.5;
	float			angle;

	angle = dot_product(reflected, col.normal);
	angle *= angle;
	angle *= angle;
	angle *= angle;
	return (color_scaling((t_color){{255, 255, 255, 0}},
		angle * specular_constant));
}

t_color	shading(const t_data *shapes, const t_col col, const t_light light)
{
	float	intensity;
	t_color	pixel_color;
	t_ray	light_ray;

	light_ray.origin = col.pos_world;
	light_ray.direction = vector_sub(light.pos, light_ray.origin);
	if (drop_shadow(shapes, light_ray, col) == 0)
		pixel_color = (t_color){{0, 0, 0, 0}};
	else
	{
		light_ray.direction = vector_normalization(light_ray.direction);
		intensity = dot_product(light_ray.direction, col.normal);
		if (intensity < EPSILON)
			pixel_color = (t_color){{0, 0, 0, 0}};
		else
		{
			pixel_color = color_mult(col.color,
					color_scaling(light.color, intensity));
			pixel_color = color_sum(pixel_color, calc_specular(col, light_ray));
		}
	}
	return (pixel_color);
}

t_color	cast_ray(const t_ray ray, const t_data *lists)
{
	const int	nb_light = lists->lights->nb_lights;
	t_color		pixel_color;
	t_col		closest;
	int			i;

	if (get_closest_collision(lists, ray, &closest) == 1)
		return (background_color(ray));
	pixel_color = (t_color){{0, 0, 0, 0}};
	i = 0;
	while (i < nb_light)
	{
		pixel_color = color_sum(pixel_color,
				shading(lists, closest, lists->lights->lights[i]));
		i++;
	}
	pixel_color = color_sum(pixel_color,
			color_mult(closest.color, lists->lights->ambient));
	return (pixel_color);
}
