/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:42:05 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/11 12:20:17 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"
#include <pthread.h>

static void	pixel_put(const t_mlx *restrict mlx, const int u,
			const int v, const t_color color)
{
	char	*dest;

	dest = mlx->img.addr + (v * mlx->img.len_line + u * mlx->img.bpp);
	*(unsigned int *)dest = color.rgba;
}

t_vec3	compute_first_pixel(const t_camera *restrict cam,
			t_vec3 *restrict delta_u, t_vec3 *restrict delta_v)
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
	const t_camera	*cam = ((t_thread_data *)data_v)->cam;
	t_thread_data	*data;
	t_color			pixel_color;
	t_vec3			width_px;
	int				uv[2];

	data = (t_thread_data *)data_v;
	uv[1] = data->start;
	while (uv[1] < data->stop)
	{
		uv[0] = 0;
		width_px = data->pixel;
		while (uv[0] < data->cam->img_width)
		{
			width_px = vector_sum(width_px, data->delta_u);
			pixel_color = cast_ray((t_ray){cam->pos, vector_sub(
						width_px, cam->pos)}, data->lists);
			pixel_put(data->mlx, uv[0], uv[1], pixel_color);
			uv[0]++;
		}
		data->pixel = vector_sum(data->pixel, data->delta_v);
		uv[1]++;
	}
	return (NULL);
}

void	fill_data(t_thread_data *data, const t_camera *cam,
			const t_lists *lists, const t_mlx *mlx)
{
	const t_vec3	first_pixel = compute_first_pixel(cam,
			&data->delta_u, &data->delta_v);
	const int		height_per_thread = cam->img_heigth / NB_THREAD;
	int				i;

	i = 0;
	while (i < NB_THREAD)
	{
		data[i].cam = (t_camera *)cam;
		data[i].lists = (t_lists *)lists;
		data[i].mlx = (t_mlx *)mlx;
		data[i].start = height_per_thread * i;
		data[i].stop = height_per_thread * (i + 1);
		data[i].delta_u = data->delta_u;
		data[i].delta_v = data->delta_v;
		data[i].pixel = vector_sum(first_pixel,
				scalar_mult(data->delta_v, data[i].start));
		if (i == NB_THREAD - 1)
			data[i].stop = data->cam->img_heigth;
		i++;
	}
}

void	launch_thread(const t_camera *restrict cam,
			const t_lists *restrict lists, const t_mlx *restrict mlx)
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
