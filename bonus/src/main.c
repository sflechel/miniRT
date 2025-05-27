/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:09 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/26 17:51:07 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "parsing.h"
#include "hook.h"
#include "mlx.h"
#include "mlx_int.h"
#include <unistd.h>

int	free_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	return (1);
}

int	init_mlx(t_mlx *mlx, t_camera *cam)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == 0)
		return (print_error_1(ERR_INIT_MLX));
	mlx->window = mlx_new_window(mlx->mlx,
			cam->img_width, cam->img_heigth, "miniRT");
	if (mlx->window == 0)
	{
		print_error_1(ERR_INIT_WINDOW);
		return (free_1_return_1(mlx->mlx));
	}
	mlx->img.img = mlx_new_image(mlx->mlx, cam->img_width, cam->img_heigth);
	if (mlx->img.img == 0)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		print_error_1(ERR_INIT_IMG);
		return (free_1_return_1(mlx->mlx));
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img,
			&mlx->img.bpp, &mlx->img.len_line, &mlx->img.endian);
	mlx->end = DONT_END;
	return (0);
}

int	main(int ac, char **av)
{
	t_camera		camera;
	t_mlx			mlx;
	t_data			shapes;
	t_light_list	*lights;
	t_hook_data		data;

	if (ac != 2)
		return (print_error_1(ERR_INVALID_NB_FILES));
	if (parsing(av[1], &shapes, &camera, &lights) == 1
		|| init_mlx(&mlx, &camera) == 1)
		return (EXIT_FAILURE);
	data = (t_hook_data){&mlx, &camera};
	handle_hooks(&data);
	while (mlx.end == DONT_END)
	{
		((t_xvar *)(mlx.mlx))->end_loop = 0;
		scan_viewport(&camera, &shapes, lights, &mlx);
		mlx_put_image_to_window(mlx.mlx, mlx.window, mlx.img.img, 0, 0);
		mlx_loop(mlx.mlx);
	}
	free_mlx(&mlx);
	return (free_3_return_0(shapes.planes, shapes.spheres, shapes.cylinders));
}
