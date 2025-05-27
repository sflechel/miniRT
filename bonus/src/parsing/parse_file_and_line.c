/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_and_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:32:09 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/26 17:59:59 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "parsing.h"
#include <stdio.h>
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
		return (print_strerror_null(ERR_INVALID_EXTENSION, filename));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (print_strerror_null(ERR_NO_OPEN, filename));
	file = read_file(fd);
	close(fd);
	return (file);
}

int	parse_line(char *line, t_data *list, t_camera *cam, t_light_list *lights)
{
	char		**params;
	char		id;

	params = ft_split(line, ' ');
	if (params == 0)
		return (1);
	id = params[0][0];
	if ((id == 'A' && handle_ambient(params, lights) == 1)
		|| (id == 'C' && handle_camera(params, cam) == 1)
		|| (id == 'L' && handle_light(params, lights) == 1)
		|| (id == 'c' && handle_cylinder(params, list->cylinders) == 1)
		|| (id == 'p' && handle_plane(params, list->planes) == 1)
		|| (id == 's' && handle_sphere(params, list->spheres) == 1))
		return (ft_free_split(params), 1);
	ft_free_split(params);
	return (0);
}
