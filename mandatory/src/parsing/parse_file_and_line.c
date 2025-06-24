/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_and_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:32:09 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/24 16:21:03 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*read_file(int fd)
{
	char	*file;
	int		nb_read;
	int		file_size;

	file_size = 1;
	file = ft_calloc(file_size, sizeof(file));
	if (file == 0)
		return (0);
	while (42)
	{
		file = ft_realloc(file, file_size * sizeof(file),
				(file_size + READ_SIZE) * sizeof(file));
		file_size += READ_SIZE;
		if (file == 0)
			return (0);
		nb_read = read(fd, file + file_size - READ_SIZE - 1, READ_SIZE);
		file[file_size + nb_read - READ_SIZE - 1] = 0;
		if (nb_read < READ_SIZE)
			break ;
	}
	if (nb_read == -1)
		return (free_1_return_null(file));
	return (file);
}

char	*open_and_read_file(char *filename)
{
	const int	dot_index = ft_strchr_last_index(filename, '.');
	int			fd;
	char		*file;

	if (dot_index == -1 || ft_strcmp(filename + dot_index, ".rt") != 0)
	{
		ft_dprintf(STDERR_FILENO,
			"Error\n%s does no end with .rt\n", filename);
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(STDERR_FILENO,
			"Error\n%s could not be opened\n", filename);
		return (NULL);
	}
	file = read_file(fd);
	close(fd);
	return (file);
}

int	parse_line(char *line, t_shape_list *list, t_camera *cam, t_light *light)
{
	static int	nb_shape = 0;
	char		**params;
	char		id;

	params = split_better(line, ' ');
	if (params == 0)
		return (1);
	id = params[0][0];
	if ((id == 'A' && handle_ambient(params, light) == 1)
		|| (id == 'C' && handle_camera(params, cam) == 1)
		|| (id == 'L' && handle_light(params, light) == 1)
		|| (id == 'c' && handle_cylinder(params, list, nb_shape) == 1)
		|| (id == 'p' && handle_plane(params, &list->array[nb_shape]) == 1)
		|| (id == 's' && handle_sphere(params, &list->array[nb_shape]) == 1))
	{
		free(params);
		return (1);
	}
	free(params);
	if (id == 'p' || id == 's')
		nb_shape++;
	else if (id == 'c')
		nb_shape += 3;
	return (0);
}
