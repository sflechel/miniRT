/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:42:05 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/30 19:05:00 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <pthread.h>

void	pixel_put(t_mlx *mlx, int u, int v, t_color color)
{
	char	*dest;

	dest = mlx->img.addr + (v * mlx->img.len_line + u * mlx->img.bpp / 8);
	*(unsigned int *)dest = color.rgba;
}

t_vec3	compute_first_pixel(t_camera *cam, t_vec3 *delta_u, t_vec3 *delta_v)
{
	t_vec3	viewport_upper_left;
	t_vec3	first_pixel;

	viewport_upper_left = vector_sub(cam->pos, cam->focal_length);
	viewport_upper_left = vector_sub(viewport_upper_left,
			scalar_mult(cam->viewport_u, 0.5));
	viewport_upper_left = vector_sub(viewport_upper_left,
			scalar_mult(cam->viewport_v, 0.5));
	*delta_u = scalar_division(cam->viewport_u, cam->img_width);
	*delta_v = scalar_division(cam->viewport_v, cam->img_heigth);
	first_pixel = vector_sum(viewport_upper_left,
			scalar_division(*delta_u, 2.));
	first_pixel = vector_sum(first_pixel, scalar_division(*delta_v, 2.));
	return (first_pixel);
}

void	*scan_viewport(void *data_v)
{
	t_thread_data	*data;
	t_color			pixel_color;
	int				uv[2];

	data = (t_thread_data *)data_v;
	uv[1] = data->start;
	while (uv[1] < data->stop)
	{
		uv[0] = 0;
		while (uv[0] < data->cam->img_width)
		{
			data->pixel = vector_sum(data->pixel, data->delta_u);
			pixel_color = cast_ray((t_ray){data->cam->pos, vector_sub(
						data->pixel, data->cam->pos)}, data->lists);
			pixel_put(data->mlx, uv[0], uv[1], pixel_color);
			uv[0]++;
		}
		data->pixel = vector_sub(data->pixel, scalar_mult(data->delta_u, data->cam->img_width));
		data->pixel = vector_sum(data->pixel, data->delta_v);
		uv[1]++;
	}
	return (NULL);
}
#define NB_THREAD 21

void	fill_data(t_thread_data *data, t_camera *cam, t_data *lists, t_mlx *mlx)
{
	int		i;

	i = 0;
	while (i < NB_THREAD)
	{
		data[i].cam = cam;
		data[i].lists = lists;
		data[i].mlx = mlx;
		data[i].start = data->cam->img_heigth / NB_THREAD * i;
		data[i].stop = data->cam->img_heigth / NB_THREAD * (i + 1);
		data[i].pixel = compute_first_pixel(cam, &data[i].delta_u, &data[i].delta_v);
		data[i].pixel = vector_sum(data[i].pixel, scalar_mult(data[i].delta_v, data[i].start));
		i++;
	}
}

void	launch_thread(t_camera *cam, t_data *lists, t_mlx *mlx)
{
	pthread_t		thrs[NB_THREAD];
	t_thread_data	data[NB_THREAD];
	int				i;

	fill_data(data, cam, lists, mlx);
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_create(thrs + i, NULL, &scan_viewport, data + i);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_join(thrs[i], NULL);
		i++;
	}
}