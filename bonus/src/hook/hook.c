/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:12:06 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/11 15:33:50 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook.h"
#include "mlx.h"
#include <X11/X.h>

static int	end_loop_destroy(void *mlx_v)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)mlx_v;
	mlx->end = END;
	mlx_loop_end(mlx->mlx);
	return (0);
}

static int	mouse_hook(int eventcode, int x, int y, t_hook_data *data)
{
	(void)x;
	(void)y;
	if (eventcode == 4)
		data->cam->vertical_fov -= 0.5;
	if (eventcode == 5)
		data->cam->vertical_fov += 0.5;
	update_camera(data->cam);
	mlx_loop_end(data->mlx->mlx);
	return (0);
}

void	handle_hooks(t_hook_data *data)
{
	mlx_hook(data->mlx->window, DestroyNotify, ResizeRedirectMask,
		&end_loop_destroy, (void *)data->mlx);
	mlx_hook(data->mlx->window, KeyPress, KeyPressMask,
		&key_hook, (void *)data);
	mlx_hook(data->mlx->window, ButtonPress, ButtonPressMask,
		&mouse_hook, (void *)data);
}
