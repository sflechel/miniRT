/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:03:54 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/11 12:20:54 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

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
	if (ft_strncmp(line, "hy ", 3) == 0)
		return (ID_HYPER);
	return (ID_ERROR);
}

static int	verify_uniques(char **lines)
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
		else if (id == ID_ERROR)
			return (print_error_1(ERR_INVALID_ID));
		i++;
	}
	if (acl[0] != 1 || acl[1] != 1 || acl[2] < 1)
		return (print_error_1(ERR_INVALID_UNIQUES));
	return (0);
}

static int	count_objects(char **lines, t_id id)
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

int	alloc_lists(char **lines, t_lists *lists,
		t_light_list **lights)
{
	const int	nb_spheres = count_objects(lines, ID_SPHERE);
	const int	nb_cylinders = count_objects(lines, ID_CYLINDER);
	const int	nb_planes = count_objects(lines, ID_PLANE);
	const int	nb_lights = count_objects(lines, ID_LIGHT);
	const int	nb_hypers = count_objects(lines, ID_HYPER);

	if (verify_uniques(lines) == 1)
		return (1);
	lists->cylinders = malloc(sizeof(t_cylinder_list)
			+ sizeof(t_cylinder) * nb_cylinders);
	lists->spheres = malloc(sizeof(t_sphere_list)
			+ sizeof(t_sphere) * nb_spheres);
	lists->planes = malloc(sizeof(t_plane_list) + sizeof(t_plane) * nb_planes);
	lists->hypers = malloc(sizeof(t_hyper_list) + sizeof(t_hyper) * nb_hypers);
	*lights = malloc(sizeof(t_light_list) + sizeof(t_light) * nb_lights);
	if (lists->cylinders == 0 || lists->spheres == 0
		|| lists->planes == 0 || *lights == 0 || lists->hypers == 0)
		return (free_lists(lists));
	lists->cylinders->nb_shapes = 0;
	lists->spheres->nb_shapes = 0;
	lists->planes->nb_shapes = 0;
	lists->hypers->nb_shapes = 0;
	(*lights)->nb_lights = 0;
	return (0);
}
