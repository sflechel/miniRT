/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:09 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/15 18:50:25 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "mlx_int.h"
#include "libft.h"
#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const float	g_aspect_ratio = 16. / 9.;

void	update_camera(t_camera *cam)
{
	t_vec3	u;
	t_vec3	v;
	
	cam->focal_length = (t_vec3){0, 0, 10};
	cam->viewport_heigth = 2 * tanf(cam->vertical_fov / 2) * cam->focal_length.z;
	cam->viewport_width = cam->viewport_heigth * ((float)cam->img_width / (float)cam->img_heigth);
	u = (t_vec3){1, 0, 0};
	v = (t_vec3){0, -1, 0};
	rotation(&u, cam->rot);
	rotation(&v, cam->rot);
	rotation(&cam->focal_length, cam->rot);
	cam->viewport_u = scalar_mult(u, cam->viewport_width);
	cam->viewport_v = scalar_mult(v, cam->viewport_heigth);
}

void	init_camera(t_camera *cam)
{
	cam->rot = (t_vec3){10, 0, 0};
	cam->rot = scalar_mult(cam->rot, M_PI / 180);
	cam->vertical_fov = 20 * M_PI / 180;
	cam->img_width = 1000;
	cam->img_heigth = cam->img_width / g_aspect_ratio;
	cam->pos = (t_vec3){0, 0,10};
	update_camera(cam);
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
	mlx->end = DONT_END;
	return (0);
}

void	sphere_constructor(t_vec3 pos, t_vec3 axis, t_color color, float radius, t_shape *shape)
{
	shape->pos = pos;
	shape->axis = axis;
	shape->color = color;
	shape->sphere.radius = radius;
	shape->get_collision = &sphere_get_collision;
	shape->get_normal = &sphere_get_normal;
}

void	plane_constructor(t_vec3 pos, t_vec3 axis, t_color color, t_vec3 normal, t_shape *shape)
{
	shape->pos = pos;
	shape->axis = axis;
	shape->color = color;
	shape->plane.normal = normal;
	shape->get_collision = &plane_get_collision;
	shape->get_normal = &plane_get_normal;
}

void	cylinder_constructor(t_vec3 pos, t_vec3 axis, t_color color, float radius, float height, t_shape *shape)
{
	shape->pos = pos;
	shape->axis = axis;
	shape->color = color;
	shape->cylinder.radius = radius;
	shape->cylinder.height = height;
	shape->get_collision = &cylinder_get_collision;
	shape->get_normal = &cylinder_get_normal;
}

int	main(void)
{
	t_camera		camera;
	t_mlx			mlx;
	t_shape			shape;
	t_shape			shape2;
	t_shape			shape3;
	t_shape			shape4;
	t_shape_list	*shapes;
	const t_light	light = (t_light){0.1, (t_vec3){-10, 2, 3}, 1};

	init_camera(&camera);
	if (init_mlx(&mlx, &camera) == 1)
		return (free_mlx(&mlx));
	shapes = malloc(sizeof(t_shape_list) + 4 * sizeof(t_shape));
	if (shapes == 0)
		return (free_mlx(&mlx));
	shapes->nb_shapes = 1;
	sphere_constructor((t_vec3){-2.5, 0, -2}, (t_vec3){0, 0, 0}, (t_color){{255, 127, 0, 0}}, 0.5, &shape);
	shapes->array[0] = shape;
	sphere_constructor((t_vec3){0, 0, -3}, (t_vec3){0, 0, 0}, (t_color){{100, 200, 42, 0}}, 2, &shape2);
	shapes->array[1] = shape2;
	plane_constructor((t_vec3){0, 0, -4}, (t_vec3){0, 0, 0}, (t_color){{50, 50, 200, 0}}, (t_vec3){0, 0, 1}, &shape3);
	shapes->array[2] = shape3;
	cylinder_constructor((t_vec3){0, 0, -2}, (t_vec3){0, 0, 0}, (t_color){{20, 150, 200, 0}}, 5, 1,&shape4);
	shapes->array[0] = shape4;
	t_hook_data data = {&mlx, &camera};
	handle_hooks(&data);
	while (mlx.end == DONT_END)
	{
		((t_xvar *)(mlx.mlx))->end_loop = 0;
		scan_viewport(&camera, shapes, light, &mlx);
		mlx_put_image_to_window(mlx.mlx, mlx.window, mlx.img.img, 0, 0);
		mlx_loop(mlx.mlx);
	}
	mlx_destroy_image(mlx.mlx, mlx.img.img);
	free_mlx(&mlx);
	free(shapes);
	return (0);
}
