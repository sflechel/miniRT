/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:09 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/13 10:23:31 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <math.h>

const float	g_aspect_ratio = 16. / 9.;

t_vec3	vector_subtraction(t_vec3 minuend, t_vec3 subtrahend)
{
	t_vec3	output;

	output.x = minuend.x - subtrahend.x;
	output.y = minuend.y - subtrahend.y;
	output.z = minuend.z - subtrahend.z;
	return (output);
}

t_vec3	vector_sum(t_vec3 term1, t_vec3 term2)
{
	t_vec3	output;

	output.x = term1.x + term2.x;
	output.y = term1.y + term2.y;
	output.z = term1.z + term2.z;
	return (output);
}

t_vec3	scalar_division(t_vec3 vec, float scalar)
{
	return ((t_vec3){vec.x / scalar, vec.y / scalar, vec.z / scalar});
}

t_vec3	scalar_multiplication(t_vec3 vec, float scalar)
{
	return ((t_vec3){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}

float	get_magnitude(t_vec3 vec)
{
	return (sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	vector_normalization(t_vec3 vec)
{
	const float	magnitude = get_magnitude(vec);

	return ((t_vec3){vec.x / magnitude, vec.y / magnitude, vec.z / magnitude});
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

t_color	background_color(t_ray ray)
{
	const t_vec3	unit_direction = vector_normalization(ray.direction);
	const float		lerp = unit_direction.y * 0.5 + 0.5;
	const t_color	white = (t_color){{0, 0, 0, 0}};
	const t_color	blue = (t_color){{255, 127, 178, 255}};
	t_color			background;

	background = color_scaling(white, 1 - lerp);
	background = color_sum(background, color_scaling(blue, lerp));
	return (background);
}

t_color cast_ray(t_ray ray, t_shape_list *shapes)
{
	t_color	pixel_color;

	(void)shapes;
	pixel_color = background_color(ray);
	return (pixel_color);
}

void	pixel_put(t_mlx *mlx, int u, int v, t_color color)
{
	char	*dest;

	color.rgba = mlx_get_color_value(mlx->mlx, color.rgba);
	dest = mlx->img.addr + (v * mlx->img.len_line + u * (mlx->img.bpp / 8));
	*(unsigned int *)dest = color.rgba;
}

void	scan_viewport(t_camera *camera, t_shape_list *shapes, t_mlx *mlx)
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
			pixel_color = cast_ray((t_ray){camera->pos, vector_subtraction(pixel, camera->pos)}, shapes);
			pixel_put(mlx, u, v, pixel_color);
			u++;
		}
		pixel = vector_subtraction(pixel, scalar_multiplication(delta_u, camera->img_width));
		pixel = vector_sum(pixel, delta_v);
		v++;
	}
}

void	init_camera(t_camera *camera)
{
	camera->focal_length = 1;
	camera->img_width = 400;
	camera->img_heigth = camera->img_width / g_aspect_ratio;
	camera->viewport_heigth = 2;
	camera->viewport_width = camera->viewport_heigth * (float)(camera->img_width / camera->img_heigth);
	camera->pos = (t_vec3){0, 0, 0};
}

int	free_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->img.img);
	free(mlx->mlx);
	return (1);
}

int	init_mlx(t_mlx *mlx, t_camera *camera)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == 0)
	{
		ft_dprintf(2, "Error\nwhen initializing minilibx");
		return (1);
	}
	mlx->window = mlx_new_window(mlx->mlx, camera->img_width, camera->img_heigth, "miniRT");
	if (mlx->window == 0)
	{
		ft_dprintf(2, "Error\nwhen creating window");
		return (1);
	}
	mlx->img.img = mlx_new_image(mlx->mlx, camera->img_width, camera->img_heigth);
	if (mlx->img.img == 0)
	{
		ft_dprintf(2, "Error\nwhen creating image");
		return (1);
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.len_line, &mlx->img.endian);
	return (0);
}

int	main(void)
{
	t_camera		camera;
	t_mlx			mlx;
	t_shape_list	*shapes;

	init_camera(&camera);
	if (init_mlx(&mlx, &camera) == 1)
		return (free_mlx(&mlx));
	shapes = malloc(sizeof(t_shape_list) + 1 * sizeof(t_shape));
	if (shapes == 0)
		return (free_mlx(&mlx));
	shapes->nb_shapes = 1;
	shapes->array[0] = (t_shape){SPHERE, (t_vec3){0, 0, 0}, (t_vec3){0, 0, 0}, (t_color){{255, 255, 255, 255}}, NULL};
	scan_viewport(&camera, shapes, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.window, mlx.img.img, 0, 0);
	mlx_loop(mlx.mlx);
	mlx_destroy_image(mlx.mlx, mlx.img.img);
	free_mlx(&mlx);
	return (0);
}
