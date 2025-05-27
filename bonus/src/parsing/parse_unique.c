/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unique.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:18:16 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/27 14:40:34 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"
#include "libft.h"
#include <stdio.h>

int	handle_ambient(char **line, t_light_list *lights)
{
	const int	len = ptr_array_len(line);
	float		ambient_intensity;

	printf("parse the ambient\n");
	if ((verif_len(len, 3) == 1)
		|| parse_form_range(line[1], &ambient_intensity, 0, 1) == 1
		|| parse_rgba(line[2], &lights->ambient) == 1)
	{
		ft_dprintf(STDERR_FILENO, " in the ambient\n");
		return (1);
	}
	lights->ambient = color_scaling(lights->ambient, ambient_intensity);
	return (0);
}

int	handle_camera(char **line, t_camera *cam, t_mlx *mlx)
{
	const int	len = ptr_array_len(line);
	t_vec3		cam_axis;

	printf("parse the cam\n");
	if (verif_len(len, 4) == 1
		|| parse_vector3(line[1], &cam->pos) == 1
		|| parse_vector3_normalised(line[2], &cam_axis) == 1
		|| parse_form_range(line[3], &cam->vertical_fov, 0, 180) == 1)
	{
		ft_dprintf(STDERR_FILENO, " in the camera\n");
		return (1);
	}
	init_camera(cam, &cam_axis, mlx);
	return (0);
}

int	handle_light(char **line, t_light_list *lights)
{
	const int	len = ptr_array_len(line);
	float		light_intensity;
	t_light		*light;

	light = &lights->lights[lights->nb_lights];
	printf("parse the light\n");
	if (verif_len(len, 4) == 1)
		return (1);
	if (parse_vector3(line[1], &light->pos) == 1
		|| parse_form_range(line[2], &light_intensity, 0, 1) == 1
		|| parse_rgba(line[3], &light->color) == 1)
	{
		ft_dprintf(STDERR_FILENO, " in the light\n");
		return (1);
	}
	light->color = color_scaling(light->color, light_intensity);
	lights->nb_lights++;
	return (0);
}
