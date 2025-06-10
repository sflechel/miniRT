/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:09 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/10 14:50:55 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "parsing.h"
#include "hook.h"
#include "mlx.h"
#include "mlx_int.h"

int	free_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	return (1);
}

int	init_mlx(t_mlx *mlx, t_camera *cam, t_shape_list *shapes)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == 0)
	{
		ft_dprintf(STDERR_FILENO, "Error\nwhen initializing minilibx\n");
		return (free_1_return_1(shapes));
	}
	mlx->window = mlx_new_window(mlx->mlx, cam->img_width,
			cam->img_heigth, "miniRT");
	if (mlx->window == 0)
	{
		mlx_destroy_display(mlx->mlx);
		ft_dprintf(STDERR_FILENO, "Error\nwhen creating window\n");
		return (free_2_return_1(mlx->mlx, shapes));
	}
	mlx->img.img = mlx_new_image(mlx->mlx, cam->img_width, cam->img_heigth);
	if (mlx->img.img == 0)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		mlx_destroy_display(mlx->mlx);
		ft_dprintf(STDERR_FILENO, "Error\nwhen creating image\n");
		return (free_2_return_1(mlx->mlx, shapes));
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img,
			&mlx->img.bpp, &mlx->img.len_line, &mlx->img.endian);
	return (0);
}

int	main(int ac, char **av)
{
	t_camera		camera;
	t_mlx			mlx;
	t_shape_list	*shapes;
	t_light			light;
	t_hook_data		data;

	if (ac != 2)
		ft_dprintf(STDERR_FILENO, "Error\nOne .rt file needed\n");
	if (ac != 2)
		return (EXIT_FAILURE);
	if (parsing(av[1], &shapes, &camera, &light) == 1
		|| init_mlx(&mlx, &camera, shapes) == 1)
		return (EXIT_FAILURE);
	data = (t_hook_data){&mlx, &camera};
	handle_hooks(&data);
	mlx.end = DONT_END;
	while (mlx.end == DONT_END)
	{
		((t_xvar *)(mlx.mlx))->end_loop = 0;
		scan_viewport(&camera, shapes, light, &mlx);
		mlx_put_image_to_window(mlx.mlx, mlx.window, mlx.img.img, 0, 0);
		mlx_loop(mlx.mlx);
	}
	free_mlx(&mlx);
	return (free_1_return_0(shapes));
}
