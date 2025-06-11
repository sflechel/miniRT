/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:18:36 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/11 12:22:06 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "parsing.h"

static int	fill_list_shapes(char **lines, t_lists *lists,
		t_camera *cam, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (parse_line(lines[i], lists, cam, mlx) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	parsing(char *filename, t_lists *lists, t_camera *cam, t_mlx *mlx)
{
	char	*file;
	char	**lines;

	file = open_and_read_file(filename);
	if (file == 0)
		return (1);
	lines = split_better(file, '\n');
	free(file);
	if (lines == 0)
		return (1);
	if (alloc_lists(lines, lists, &lists->lights) == 1)
	{
		free_mlx(mlx);
		return (free_1_return_1(lines));
	}
	if (fill_list_shapes(lines, lists, cam, mlx) == 1)
	{
		free_lists_and_img(lists, mlx);
		free_mlx(mlx);
		return (free_1_return_1(lines));
	}
	return (free_1_return_0(lines));
}
