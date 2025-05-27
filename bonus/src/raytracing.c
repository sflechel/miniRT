/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:43:53 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/27 12:04:17 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"
#include "libft.h"
#include "shapes.h"

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

t_vec3 get_light_ray_reflected(t_col col, t_ray light_ray)
{
	const t_vec3	reflect_proj = ortho_proj(light_ray.direction, col.normal);
	const t_vec3	mult_by_2 = scalar_mult(reflect_proj, 2);
	const t_vec3	reflected = vector_subtraction(mult_by_2, light_ray.direction);
	
	return (reflected);
}

float	calc_specular(t_col col, t_ray light_ray, t_ray ray)
{
	
	const t_vec3	reflected = get_light_ray_reflected(col, light_ray);
	const float		specular_constant = 0.1;
	const float		dot = dot_product(reflected, ray.direction);
	
	return (dot * dot * specular_constant);
}

t_color	shading(t_data *shapes, t_col col, t_light light)
{
	float	intensity;
	t_color	pixel_color;
	t_ray	light_ray;

	light_ray.origin = col.pos_world;
	light_ray.direction = vector_subtraction(light.pos, light_ray.origin);
	if (there_is_collision(shapes, light_ray))
		pixel_color = (t_color){{0, 0, 0, 0}};
	else
	{
		light_ray.direction = vector_normalization(light_ray.direction);
		intensity = dot_product(light_ray.direction, col.normal);
		if (intensity < 0)
			pixel_color = (t_color){{0, 0, 0, 0}};
		else
			pixel_color = color_mult(col.color, color_scaling(light.color, intensity));
	}
	return (pixel_color);
}

t_color	cast_ray(t_ray ray, t_data *shapes, t_light_list *lights)
{
	t_color	pixel_color;
	t_col	col;
	int		i;

	if (get_closest_collision(shapes, ray, &col) == -1)
		return (background_color(ray));
	ft_memset(&pixel_color, 0, sizeof(t_color));
	i = 0;
	while (i < lights->nb_lights)
	{
		pixel_color = color_sum(pixel_color, shading(shapes, col, lights->lights[i]));
		i++;
	}
	pixel_color = color_sum(pixel_color, color_mult(col.color, lights->ambient));
	return (pixel_color);
}
