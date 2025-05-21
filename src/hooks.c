/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:12:06 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/21 17:03:25 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <X11/X.h>
#include <X11/keysymdef.h>
#include <stdio.h>

void	change_pos_camera(t_vec3 dpos, t_camera *cam)
{
	rotation(&dpos, cam->rot);
	cam->pos = vector_sum(dpos, cam->pos);
}

int	end_loop_esc(int keycode, void *data_v)
{
	const t_hook_data	*data = (t_hook_data *)data_v;

	if (keycode == 65307)
		data->mlx->end = END;
	else if (keycode == 'w')
		change_pos_camera((t_vec3){0, 0, 0.2}, data->cam);
	else if (keycode == 's')
		change_pos_camera((t_vec3){0, 0, -0.2}, data->cam);
	else if (keycode == 'a')
		change_pos_camera((t_vec3){0.2, 0, 0}, data->cam);
	else if (keycode == 'd')
		change_pos_camera((t_vec3){-0.2, 0, 0}, data->cam);
	else if (keycode == 0xffe1)
		change_pos_camera((t_vec3){0, 0.2, 0}, data->cam);
	else if (keycode == ' ')
		change_pos_camera((t_vec3){0, -0.2, 0}, data->cam);
	else if (keycode == 65361)
		data->cam->rot.y += 0.02;
	else if (keycode == 65362)
		data->cam->rot.x += .02;
	else if (keycode == 65363)
		data->cam->rot.y -= .02;
	else if (keycode == 65364)
		data->cam->rot.x -= .02;
	else if (keycode == '0')
		data->cam->rot.z += .02;
	else if (keycode == '.')
		data->cam->rot.z -= .02;
	printf("%f, %f, %f\n", data->cam->pos.x, data->cam->pos.y, data->cam->pos.z);
	printf("%f, %f, %f\n", data->cam->rot.x, data->cam->rot.y, data->cam->rot.z);
	printf("move or rotate\n");
	update_camera(data->cam);
	mlx_loop_end(data->mlx->mlx);
	return (0);
}

int	end_loop_destroy(void *mlx_v)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_v;
	mlx->end = END;
	mlx_loop_end(mlx->mlx);
	return (0);
}

int	mouse_hook(int eventcode, int x, int y, t_hook_data *data)
{
	(void)x;
	(void)y;
	if (eventcode == 4)
		data->cam->vertical_fov -= 0.05;
	if (eventcode == 5)
		data->cam->vertical_fov += 0.05;
	update_camera(data->cam);
	mlx_loop_end(data->mlx->mlx);
	return (0);
}

void	handle_hooks(t_hook_data *data)
{
	mlx_hook(data->mlx->window,
		DestroyNotify, ResizeRedirectMask, &end_loop_destroy, (void *)data->mlx);
	mlx_hook(data->mlx->window,
		KeyPress, KeyPressMask, &end_loop_esc, (void *)data);
	mlx_hook(data->mlx->window, ButtonPress, ButtonPressMask, mouse_hook, (void *)data);
}
