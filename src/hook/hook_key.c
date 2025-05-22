/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:59:55 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/22 18:13:11 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "hook.h"
#include "mlx.h"

static void	change_pos_camera(t_vec3 dpos, t_camera *cam)
{
	rotation(&dpos, cam->rot);
	cam->pos = vector_sum(dpos, cam->pos);
}

static void	handle_hook_cam(int keycode, t_camera *cam)
{
	if (keycode == KEY_W)
		change_pos_camera((t_vec3){0, 0, -0.4}, cam);
	else if (keycode == KEY_S)
		change_pos_camera((t_vec3){0, 0, 0.4}, cam);
	else if (keycode == KEY_A)
		change_pos_camera((t_vec3){-0.4, 0, 0}, cam);
	else if (keycode == KEY_D)
		change_pos_camera((t_vec3){0.4, 0, 0}, cam);
	else if (keycode == KEY_LSHIFT)
		change_pos_camera((t_vec3){0, -0.4, 0}, cam);
	else if (keycode == KEY_SPACE)
		change_pos_camera((t_vec3){0, 0.4, 0}, cam);
}

int	key_hook(int keycode, void *data_v)
{
	const t_hook_data	*data = (t_hook_data *)data_v;

	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D || keycode == KEY_LSHIFT || keycode == KEY_SPACE)
		handle_hook_cam(keycode, data->cam);
	else if (keycode == KEY_ARROW_LEFT)
		data->cam->rot.y += 0.02;
	else if (keycode == KEY_ARROW_RIGHT)
		data->cam->rot.y -= .02;
	else if (keycode == KEY_ARROW_UP)
		data->cam->rot.x += .02;
	else if (keycode == KEY_ARROW_DOWN)
		data->cam->rot.x -= .02;
	else if (keycode == KEY_MINUS)
		data->cam->rot.z += .02;
	else if (keycode == KEY_EQUAL)
		data->cam->rot.z -= .02;
	else if (keycode == KEY_ESCAPE)
		data->mlx->end = END;
	update_camera(data->cam);
	mlx_loop_end(data->mlx->mlx);
	return (0);
}
