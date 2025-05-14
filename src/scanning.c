/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:42:05 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/13 18:44:40 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

void	pixel_put(t_mlx *mlx, int u, int v, t_color color)
{
	char	*dest;

	color.rgba = mlx_get_color_value(mlx->mlx, color.rgba);
	dest = mlx->img.addr + (v * mlx->img.len_line + u * (mlx->img.bpp / 8));
	*(unsigned int *)dest = color.rgba;
}

t_vec3	compute_first_pixel(t_camera *camera, t_vec3 *delta_u, t_vec3 *delta_v)
{
	t_vec3	viewport_upper_left;
	t_vec3	first_pixel;

	viewport_upper_left = vector_subtraction(camera->pos,
			(t_vec3){camera->viewport_width / 2, camera->viewport_heigth / -2, camera->focal_length});
	*delta_u = (t_vec3){camera->viewport_width / camera->img_width, 0, 0};
	*delta_v = (t_vec3){0, -camera->viewport_heigth / camera->img_heigth, 0};
	first_pixel = vector_sum(viewport_upper_left, scalar_division(*delta_u, 2.));
	first_pixel = vector_sum(first_pixel, scalar_division(*delta_v, 2.));
	return (first_pixel);
}

void	scan_viewport(t_camera *camera, t_shape_list *shapes, t_light light, t_mlx *mlx)
{
	t_vec3	delta_u;
	t_vec3	delta_v;
	t_vec3	pixel;
	t_color	pixel_color;
	int		u;
	int		v;

	v = 0;
	pixel = compute_first_pixel(camera, &delta_u, &delta_v);
	while (v < camera->img_heigth)
	{
		u = 0;
		while (u < camera->img_width)
		{
			pixel = vector_sum(pixel, delta_u);
			pixel_color = cast_ray((t_ray){camera->pos, vector_subtraction(pixel, camera->pos)}, shapes, light);
			pixel_put(mlx, u, v, pixel_color);
			u++;
		}
		pixel = vector_subtraction(pixel, scalar_multiplication(delta_u, camera->img_width));
		pixel = vector_sum(pixel, delta_v);
		v++;
	}
}
