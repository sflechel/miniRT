/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:14:43 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/16 14:55:48 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"
#include <math.h>

void	update_camera(t_camera *cam)
{
	t_vec3	u;
	t_vec3	v;

	cam->focal_length = (t_vec3){0, 0, 10};
	cam->viewport_width = 2 * tanf(cam->horizontal_fov / 90 * M_PI)
		* cam->focal_length.z;
	cam->viewport_heigth = cam->viewport_width
		* ((float)cam->img_heigth / (float)cam->img_width);
	u = (t_vec3){1, 0, 0};
	v = (t_vec3){0, -1, 0};
	rotation(&u, cam->rot);
	rotation(&v, cam->rot);
	rotation(&cam->focal_length, cam->rot);
	cam->viewport_u = scalar_mult(u, cam->viewport_width);
	cam->viewport_v = scalar_mult(v, cam->viewport_heigth);
}

void	init_camera(t_camera *cam, t_vec3 *cam_axis, t_mlx *mlx)
{
	float		cosa;
	float		cost;
	t_vec3		a;

	cam->img_heigth = mlx->img.height;
	cam->img_width = mlx->img.width;
	cosa = dot_product(*cam_axis, (t_vec3){0, 0, 1});
	if (cosa >= -1 - EPSILON && cosa <= -1 + EPSILON)
	{
		cam->rot.x = M_PI;
		cam->rot.y = 0;
		cam->rot.z = 0;
		update_camera(cam);
		return ;
	}
	a = cross_product(*cam_axis, (t_vec3){0, 0, 1});
	cam->rot.y = -asinf(-a.y + (a.x * a.z) / (1 + cosa));
	cost = 1 / cosf(cam->rot.y);
	cam->rot.x = atan2f((a.x + (a.z * a.y) / (1 + cosa))
			* cost, (1 + (-a.x * a.x + -a.y * a.y) / (1 + cosa)) * cost);
	cam->rot.z = atan2f((a.z + (a.x * a.y) / (1 + cosa))
			* cost, (1 + (-a.z * a.z + -a.y * a.y) / (1 + cosa)) * cost);
	update_camera(cam);
}
