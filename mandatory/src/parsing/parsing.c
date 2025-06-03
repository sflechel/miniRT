/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:18:36 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/03 17:02:54 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <unistd.h>

static char	is_valid_id(char *line)
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
			nb_shapes += 3;
		else if (id == ID_AMBIENT || id == ID_CAMERA || id == ID_LIGHT)
			acl[(int)id] += 1;
		else
			return (-1);
		i++;
	}
	if (acl[0] != 1 || acl[1] != 1 || acl[2] != 1)
		return (-2);
	return (nb_shapes);
}

int	alloc_list_shapes(char **lines, t_shape_list **list)
{
	const int	nb_shapes = count_shapes_and_verify(lines);

	if (nb_shapes < 0)
	{
		ft_dprintf(STDERR_FILENO,"Error\nInvalid ");
		if (nb_shapes == -1)
			ft_dprintf(STDERR_FILENO,"shape id\n");
		else
			ft_dprintf(STDERR_FILENO,
				"amount of requiered params(cam, ambient, light)\n");
		return (1);
	}
	*list = malloc(sizeof(t_shape_list) + sizeof(t_shape) * nb_shapes);
	if (*list == 0)
		return (1);
	(*list)->nb_shapes = nb_shapes;
	return (0);
}

int	fill_list_shapes(char **lines, t_shape_list *list, t_camera *cam,
		t_light *light)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (parse_line(lines[i], list, cam, light) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	parsing(char *filename, t_shape_list **list, t_camera *cam,
		t_light *light)
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
	if (alloc_list_shapes(lines, list) == 1)
		return (free_1_return_1(lines));
	if (fill_list_shapes(lines, *list, cam, light) == 1)
		return (free_2_return_1(lines, *list));
	return (free_1_return_0(lines));
}
