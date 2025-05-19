/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:18:36 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/16 14:59:57 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_SIZE 100

char	*read_file(int fd)
{
	char	*file;
	int		nb_read;
	int		file_size;

	file = malloc(READ_SIZE + 1);
	file_size = READ_SIZE + 1;
	if (file == 0)
		return (0);
	while (42)
	{
		file = ft_realloc(file, file_size, file_size + READ_SIZE);
		if (file == 0)
			return (0);
		nb_read = read(fd, file + file_size, READ_SIZE);
		if (nb_read < READ_SIZE)
			break ;
		file[file_size + nb_read] = 0;
		file_size += READ_SIZE;
	}
	if (nb_read == -1)
		return (free_1_return_null(file));
	return (file);
}

typedef enum e_id
{
	ID_CORRECT,
	ID_AMBIENT = 1,
	ID_CAMERA = 2,
	ID_LIGHT = 3,
	ID_CYLINDER,
	ID_ERROR
}	t_id;

char	is_valid_id(char *line)
{
	if (ft_strncmp(line, "A ", 2) == 0)
		return (ID_AMBIENT);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (ID_CAMERA);
	if (ft_strncmp(line, "L ", 2) == 0)
		return (ID_LIGHT);
	if (ft_strncmp(line, "sp ", 3) == 0)
		return (ID_CORRECT);
	if (ft_strncmp(line, "cy ", 3) == 0)
		return (ID_CYLINDER);
	if (ft_strncmp(line, "pl ", 3) == 0)
		return (ID_CORRECT);
	return (ID_ERROR);
}

int	count_shapes_and_verify(char **lines)
{
	int		nb_shapes;
	int		i;
	char	id;
	char	acl[3];

	i = 0;
	nb_shapes = 0;
	ft_memset(&acl, 0, sizeof(char) * 3);
	while (lines[i])
	{
		id = is_valid_id(lines[i]);
		if (id == ID_CORRECT)
			nb_shapes++;
		else if (id == ID_CYLINDER)
			nb_shapes += 2;
		else if (id == ID_AMBIENT || id == ID_CAMERA || id == ID_LIGHT)
			acl[id]++;
		else
			return (-1);
		i++;
	}
	if (acl[0] != 1 || acl[1] != 1 || acl[2] != 1)
		return (-1);
	return (nb_shapes);
}

int	alloc_list_shapes(char **lines, t_shape_list **list)
{
	const int	nb_shapes = count_shapes_and_verify(lines);

	if (nb_shapes == -1)
		return (1);
	*list = malloc(sizeof(t_shape_list) + sizeof(t_shape) * nb_shapes);
	if (*list == 0)
		return (1);
	(*list)->nb_shapes = nb_shapes;
	return (0);
}

int handle_ambient(char **line, t_light *light)
{
	const int	len = ptr_array_len(line);

	if (len != 3)
		return (1);

}

int	handle_line(char *line, t_shape *shape, t_camera *cam, t_light *light)
{
	const char	**split_line = (const char **)ft_split(line, ' ');

	if (split_line == 0)
		return (1);
	if (split_line[0][0] == 'A' && handle_ambient((char **)split_line, light) == 1)
		return (ft_free_split((char **)split_line), 1);
	if (split_line[0][0] == 'C' && handle_camera((char **)split_line, cam) == 1)
		return (ft_free_split((char **)split_line), 1);
	if (split_line[0][0] == 'L' && handle_light((char **)split_line, light) == 1)
		return (ft_free_split((char **)split_line), 1);
	if (split_line[0][0] == 'c' && handle_cylinder((char **)split_line, shape) == 1)
		return (ft_free_split((char **)split_line), 1);
	if (split_line[0][0] == 'p' && handle_plane((char **)split_line, shape) == 1)
		return (ft_free_split((char **)split_line), 1);
	if (split_line[0][0] == 's' && handle_sphere((char **)split_line, shape) == 1)
		return (ft_free_split((char **)split_line), 1);
	return (0);
}

int	fill_data_structs(char **lines, t_shape_list *list, t_camera *cam, t_light *light)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (handle_line(lines[i], &list->array[i], cam, light) == 1)
			return (1);
		i++;
	}
}

int	parse_file(char *filename, t_shape_list **list, t_camera *cam, t_light *light)
{
	char	*file;
	char	**lines;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	file = read_file(fd);
	close(fd);
	if (file == 0)
		return (1);
	lines = ft_split(file, '\n');
	free(file);
	if (lines == 0)
		return (1);
	if (alloc_list_shapes(lines, list) == 1)
		return (ft_free_split(lines), 1);
	if (fill_data_structs(lines, *list, cam, light) == 1)
		return (ft_free_split(lines), free(*list), 1);
	return (0);
}
