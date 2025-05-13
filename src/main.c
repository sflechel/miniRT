/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:09 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/13 18:01:30 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>

const float	g_aspect_ratio = 16. / 9.;

void	init_camera(t_camera *camera)
{
	camera->focal_length = 1;
	camera->img_width = 1920;
	camera->img_heigth = camera->img_width / g_aspect_ratio;
	camera->viewport_heigth = 3;
	camera->viewport_width = camera->viewport_heigth * ((float)camera->img_width / (float)camera->img_heigth);
	camera->pos = (t_vec3){0, 0,0};
}

int	free_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
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

void	sphere_constructor(t_vec3 pos, t_vec3 rot, t_color color, float radius, t_shape *shape)
{
	shape->pos = pos;
	shape->rot = rot;
	shape->color = color;
	shape->sphere.radius = radius;
	shape->get_collision = &sphere_get_collision;
	shape->get_normal = &sphere_get_normal;
}

int	main(void)
{
	t_camera		camera;
	t_mlx			mlx;
	t_shape			shape;
	t_shape			shape2;
	t_shape_list	*shapes;
	const t_light	light = (t_light){0.1, (t_vec3){1, 1, -3}, 1};

	init_camera(&camera);
	if (init_mlx(&mlx, &camera) == 1)
		return (free_mlx(&mlx));
	shapes = malloc(sizeof(t_shape_list) + 2 * sizeof(t_shape));
	if (shapes == 0)
		return (free_mlx(&mlx));
	shapes->nb_shapes = 2;
	sphere_constructor((t_vec3){1, -0.5, -1}, (t_vec3){0, 0, 0}, (t_color){{255, 127, 0, 0}}, 0.5, &shape);
	shapes->array[0] = shape;
	sphere_constructor((t_vec3){-2, 1, -3}, (t_vec3){0, 0, 0}, (t_color){{100, 200, 42, 0}}, 2, &shape2);
	shapes->array[1] = shape2;
	handle_hooks(&mlx);
	scan_viewport(&camera, shapes, light, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.window, mlx.img.img, 0, 0);
	mlx_loop(mlx.mlx);
	mlx_destroy_image(mlx.mlx, mlx.img.img);
	free_mlx(&mlx);
	free(shapes);
	return (0);
}
