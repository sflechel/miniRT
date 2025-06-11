/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:43:27 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/11 11:46:39 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include <stdlib.h>

int	free_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	return (1);
}

int	free_lists(t_data *lists)
{
	free(lists->hypers);
	free(lists->lights);
	free(lists->planes);
	free(lists->spheres);
	free(lists->cylinders);
	return (1);
}

void	free_imgs(t_image *img1, t_image *img2, t_mlx *mlx)
{
	if (img1 != 0)
	{
		mlx_destroy_image(mlx->mlx, img1->img);
		free(img1);
	}
	if (img2 != 0)
	{
		mlx_destroy_image(mlx->mlx, img2->img);
		free(img2);
	}
}

void	free_lists_and_img(t_data *lists, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < lists->cylinders->nb_shapes || i < lists->planes->nb_shapes
		|| i < lists->spheres->nb_shapes || i < lists->hypers->nb_shapes)
	{
		if (i < lists->cylinders->nb_shapes)
			free_imgs(lists->cylinders->array[i].txtr,
				lists->cylinders->array[i].bump, mlx);
		if (i < lists->planes->nb_shapes)
			free_imgs(lists->planes->array[i].txtr,
				lists->planes->array[i].bump, mlx);
		if (i < lists->spheres->nb_shapes)
			free_imgs(lists->spheres->array[i].txtr,
				lists->spheres->array[i].bump, mlx);
		if (i < lists->hypers->nb_shapes)
			free_imgs(lists->hypers->array[i].txtr,
				lists->hypers->array[i].bump, mlx);
		i++;
	}
	free_lists(lists);
}
