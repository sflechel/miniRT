/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:18:36 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/26 15:08:18 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

static t_id	is_valid_id(char *line)
{
	if (ft_strncmp(line, "A ", 2) == 0)
		return (ID_AMBIENT);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (ID_CAMERA);
	if (ft_strncmp(line, "L ", 2) == 0)
		return (ID_LIGHT);
	if (ft_strncmp(line, "sp ", 3) == 0)
		return (ID_SPHERE);
	if (ft_strncmp(line, "cy ", 3) == 0)
		return (ID_CYLINDER);
	if (ft_strncmp(line, "pl ", 3) == 0)
		return (ID_PLANE);
	return (ID_ERROR);
}

int	verify_uniques(char **lines)
{
	int		i;
	char	id;
	char	acl[3];

	i = 0;
	ft_memset(&acl, 0, sizeof(char) * 3);
	while (lines[i])
	{
		id = is_valid_id(lines[i]);
		if (id == ID_AMBIENT || id == ID_CAMERA || id == ID_LIGHT)
			acl[(int)id] += 1;
		else
			return (print_error_1(ERR_INVALID_ID));
		i++;
	}
	if (acl[0] != 1 || acl[1] != 1 || acl[2] != 1)
		return (print_error_1(ERR_INVALID_UNIQUES));
	return (0);
}

int	count_shapes(char **lines, t_id id)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (lines[i])
	{
		if (is_valid_id(lines[i]) == id)
			count++;
		i++;
	}
	return (count);
}

int	alloc_list_shapes(char **lines, t_data *list)
{
	const int	nb_spheres = count_shapes(lines, ID_SPHERE);
	const int	nb_cylinders = count_shapes(lines, ID_CYLINDER);
	const int	nb_planes = count_shapes(lines, ID_PLANE);

	if (verify_uniques(lines) == 1)
		return (1);
	list->cylinders = malloc(sizeof(t_cylinder_list)
			+ sizeof(t_cylinder) * nb_cylinders);
	list->spheres = malloc(sizeof(t_sphere_list)
			+ sizeof(t_sphere) * nb_spheres);
	list->planes = malloc(sizeof(t_plane_list) + sizeof(t_plane) * nb_planes);
	if (list->cylinders == 0 || list->spheres == 0 || list->planes == 0)
		return (free_3_return_1(list->planes, list->spheres, list->cylinders));
	list->cylinders->nb_shapes = 0;
	list->spheres->nb_shapes = 0;
	list->planes->nb_shapes = 0;
	return (0);
}

int	fill_list_shapes(char **lines, t_data *list, t_camera *cam,
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

int	parsing(char *filename, t_data *list, t_camera *cam,
		t_light *light)
{
	char	*file;
	char	**lines;

	file = open_and_read_file(filename);
	if (file == 0)
		return (1);
	lines = ft_split(file, '\n');
	free(file);
	if (lines == 0)
		return (1);
	if (alloc_list_shapes(lines, list) == 1)
		return (ft_free_split(lines), 1);
	if (fill_list_shapes(lines, list, cam, light) == 1)
		return (ft_free_split(lines), free(list->planes), free(list->spheres), free(list->cylinders), 1);
	ft_free_split(lines);
	return (0);
}
