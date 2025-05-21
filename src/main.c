/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:09 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/21 13:09:08 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "mlx_int.h"
#include <X11/X.h>
#include <stdlib.h>

const float	g_aspect_ratio = 16. / 9.;

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
		printf("Error\nwhen initializing minilibx");
		return (1);
	}
	mlx->window = mlx_new_window(mlx->mlx, camera->img_width, camera->img_heigth, "miniRT");
	if (mlx->window == 0)
	{
		printf("Error\nwhen creating window");
		return (1);
	}
	mlx->img.img = mlx_new_image(mlx->mlx, camera->img_width, camera->img_heigth);
	if (mlx->img.img == 0)
	{
		printf("Error\nwhen creating image");
		return (1);
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.len_line, &mlx->img.endian);
	mlx->end = DONT_END;
	return (0);
}

int	main(int ac, char **av)
{
	t_camera		camera;
	t_mlx			mlx;
	t_shape_list	*shapes;
	t_light			light;

	if (ac != 2)
		return (EXIT_FAILURE);
	init_camera(&camera);
	if (parsing(av[1], &shapes, &camera, &light) == 1)
		return (EXIT_FAILURE);
	if (init_mlx(&mlx, &camera) == 1)
		return (free_mlx(&mlx));
	update_camera(&camera);
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
