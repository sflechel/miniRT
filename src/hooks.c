/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:12:06 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/13 10:26:41 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <X11/X.h>

int	end_loop_esc(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
	{
		mlx_loop_end(mlx->mlx);
	}
	return (0);
}

int	end_loop_destroy(t_mlx *mlx)
{
	mlx_loop_end(mlx->mlx);
	return (0);
}

void	handle_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->window,
		DestroyNotify, ResizeRedirectMask, end_loop_destroy, mlx);
	mlx_hook(mlx->window,
		KeyPress, KeyPressMask, end_loop_esc, mlx);
}
