/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unique.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:18:16 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/10 14:17:35 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "minirt.h"
#include "parsing.h"
#include "libft.h"
#include <stdio.h>

int	handle_ambient(char **line, t_light *light)
{
	const int	len = ptr_array_len(line);
	float		ambient_intensity;

	printf("parse the ambient\n");
	if ((verif_len(len, 3) == 1)
		|| parse_form_range(line[1], &ambient_intensity, 0, 1) == 1
		|| parse_rgba(line[2], &light->ambient) == 1)
	{
		ft_dprintf(STDERR_FILENO, " in the ambient\n");
		return (1);
	}
	light->ambient = color_scaling(light->ambient, ambient_intensity);
	return (0);
}

int	handle_camera(char **line, t_camera *cam)
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
	init_camera(cam, &cam_axis);
	return (0);
}

int	handle_light(char **line, t_light *light)
{
	const int	len = ptr_array_len(line);
	t_color		unused_colored;

	printf("parse the light\n");
	if (verif_len(len, 4) == 1
		|| parse_vector3(line[1], &light->pos) == 1
		|| parse_form_range(line[2], &light->brightness, 0, 1) == 1
		|| parse_rgba(line[3], &unused_colored) == 1)
	{
		ft_dprintf(STDERR_FILENO, " in the light\n");
		return (1);
	}
	return (0);
}
