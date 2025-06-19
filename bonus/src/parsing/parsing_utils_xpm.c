/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_xpm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:31:34 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/18 09:57:14 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "mlx.h"
#include <unistd.h>

int	parse_xpm(char *str, t_image **img, t_mlx *mlx)
{
	if (ft_strcmp(str, "0") == 0)
	{
		*img = 0;
		return (0);
	}
	*img = ft_calloc(1, sizeof(t_image));
	if (*img == 0)
		return (1);
	(*img)->img
		= mlx_xpm_file_to_image(mlx->mlx, str, &(*img)->width, &(*img)->height);
	if ((*img)->img == 0)
	{
		print_strerror_null(ERR_XPM, str);
		free(*img);
		*img = 0;
		return (1);
	}
	(*img)->addr = mlx_get_data_addr(
			(*img)->img, &(*img)->bpp, &(*img)->len_line, &(*img)->endian);
	(*img)->bpp /= 8;
	return (0);
}

int	verif_texture_size(t_image *txtr, t_image *bump)
{
	if (txtr == 0 || bump == 0)
		return (0);
	if (txtr->height != bump->height || txtr->width != bump->width)
	{
		ft_dprintf(STDERR_FILENO,
			"Error\nBoth textures must be of the same size");
		return (1);
	}
	return (0);
}

int	parse_xpms(char *strs[], t_image **txtr, t_image **bump, t_mlx *mlx)
{
	const char	*str1 = strs[0];
	const char	*str2 = strs[1];

	if (parse_xpm((char *)str1, txtr, mlx) == 1)
		return (1);
	if (parse_xpm((char *)str2, bump, mlx) == 1)
	{
		if (!txtr)
		{
			mlx_destroy_image(mlx->mlx, (*txtr)->img);
			free((*txtr));
		}
		return (1);
	}
	if (verif_texture_size(*txtr, *bump) == 1)
	{
		mlx_destroy_image(mlx->mlx, (*txtr)->img);
		free((*txtr));
		mlx_destroy_image(mlx->mlx, (*bump)->img);
		free((*bump));
		return (1);
	}
	return (0);
}
