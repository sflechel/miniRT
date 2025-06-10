/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:43:27 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/10 13:48:35 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include <stdlib.h>

void	free_img(t_image *img, t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, img->img);
	free(img);
}

void	free_imgs(t_cylinder_list *list, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < list->nb_shapes)
	{
		if (list->array[i].txtr != 0)
			free_img(list->array[i].txtr, mlx);
		if (list->array[i].bump != 0)
			free_img(list->array[i].bump, mlx);
		i++;
	}
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

int	free_lists_and_img(t_data *lists, t_mlx *mlx)
{
	free_imgs(lists->cylinders, mlx);
	free_imgs((t_cylinder_list *)lists->hypers, mlx);
	free_imgs((t_cylinder_list *)lists->spheres, mlx);
	free_imgs((t_cylinder_list *)lists->planes, mlx);
	free(lists->hypers);
	free(lists->lights);
	free(lists->planes);
	free(lists->spheres);
	free(lists->cylinders);
	return (1);
}

int	free_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window(mlx->mlx, mlx->window);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	return (1);
}