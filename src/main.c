/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:09 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/13 10:44:46 by sflechel         ###   ########.fr       */
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
	camera->img_width = 1080;
	camera->img_heigth = camera->img_width / g_aspect_ratio;
	camera->viewport_heigth = 2;
	camera->viewport_width = camera->viewport_heigth * (float)(camera->img_width / camera->img_heigth);
	camera->pos = (t_vec3){0, 0, 0};
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
	handle_hooks(&mlx);
	scan_viewport(&camera, shapes, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.window, mlx.img.img, 0, 0);
	mlx_loop(mlx.mlx);
	mlx_destroy_image(mlx.mlx, mlx.img.img);
	free_mlx(&mlx);
	free(shapes);
	return (0);
}
