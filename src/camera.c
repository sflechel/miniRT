/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:14:43 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/16 11:15:30 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

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
	cam->rot = (t_vec3){0, 0, 0};
	cam->rot = scalar_mult(cam->rot, M_PI / 180);
	cam->vertical_fov = 20 * M_PI / 180;
	cam->img_width = 1000;
	cam->img_heigth = cam->img_width / g_aspect_ratio;
	cam->pos = (t_vec3){0, 0,10};
	update_camera(cam);
}
