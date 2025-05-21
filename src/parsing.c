/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:18:36 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/21 17:08:49 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <X11/X.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_SIZE 100

char	*read_file(int fd)
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
		file = ft_realloc(file, file_size * sizeof(file), (file_size + READ_SIZE) * sizeof(file));
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

typedef enum e_id
{
	ID_AMBIENT = 0,
	ID_CAMERA = 1,
	ID_LIGHT = 2,
	ID_CORRECT,
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
		printf("Error\nInvalid ");
		if (nb_shapes == -1)
			printf("shape id\n");
		else
			printf(
					"amount of requiered params(cam, ambient, light)\n");
		return (1);
	}
	*list = malloc(sizeof(t_shape_list) + sizeof(t_shape) * nb_shapes);
	if (*list == 0)
		return (1);
	(*list)->nb_shapes = nb_shapes;
	return (0);
}

int	parse_rgba(char *str, t_color *color)
{
	const char	**rgba = (const char **)ft_split(str, ',');
	const int	len = ptr_array_len((char **)rgba);
	const int	r = color->r;
	const int	g = color->g;
	const int	b = color->b;

	if (len != 3
		|| safe_atoi(rgba[0], (int *)&r) == 1 || r < 0 || r > 255
		|| safe_atoi(rgba[1], (int *)&g) == 1 || g < 0 || g > 255
		|| safe_atoi(rgba[2], (int *)&b) == 1 || b < 0 || b > 255)
	{
		printf("Error\n%s is not a valid color", str);
		ft_free_split((char **)rgba);
		return (1);
	}
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = 0;
	ft_free_split((char **)rgba);
	return (0);
}

int	parse_form_range(char *str, float *range, float min, float max)
{
	if (safe_atof(str, range) == 1
		|| *range < min || *range > max)
	{
		printf("Error\n%s is not a valid float in range %f %f", str, min, max);
		return (1);
	}
	return (0);
}

int	parse_vector3(char *str, t_vec3 *vec)
{
	const char	**vector = (const char **)ft_split(str, ',');
	const int	len = ptr_array_len((char **)vector);

	if (len != 3
		|| safe_atof(vector[0], &vec->x) == 1
		|| safe_atof(vector[1], &vec->y) == 1
		|| safe_atof(vector[2], &vec->z) == 1)
	{
		printf("Error\n%s is not a valid vector 3", str);
		ft_free_split((char **)vector);
		return (1);
	}
	ft_free_split((char **)vector);
	return (0);
}

int	parse_vector3_normalised(char *str, t_vec3 *vec)
{
	if (parse_vector3(str, vec) == 1 || get_norm(*vec) != 1)
		return (1);
	return (0);
}

int	handle_ambient(char **line, t_light *light)
{
	const int	len = ptr_array_len(line);

	printf("parse the ambient\n");
	if (len != 3
		|| parse_form_range(line[1], &light->ambient, 0, 1) == 1
		|| parse_rgba(line[2], &light->ambient_color) == 1)
	{
		printf(" in the ambient\n");
		return (1);
	}
	return (0);
}

int	handle_camera(char **line, t_camera *cam)
{
	const int	len = ptr_array_len(line);
	t_vec3		cam_axis;
	t_vec3		a;
	float		cosa;
	float		cost;

	printf("parse the cam\n");
	if (len != 4
		|| parse_vector3(line[1], &cam->pos) == 1
		|| parse_vector3_normalised(line[2], &cam_axis) == 1
		|| parse_form_range(line[3], &cam->vertical_fov, 0, 180) == 1)
	{
		printf(" in the camera\n");
		return (1);
	}
	cosa = dot_product(cam_axis, (t_vec3){0, 1, 0});
	a = cross_product(cam_axis, (t_vec3){0, 1, 0});
	cam->rot.y = -asinf(-a.y + (a.x * a.z) / (1 + cosa));
	cost = 1 / cosf(cam->rot.y);
	cam->rot.x = atan2f((a.x + (a.z * a.y) / (1 + cosa)) * cost, (1 + (-a.x * a.x + -a.y * a.y) / (1 + cosa)) * cost);
	cam->rot.z = atan2f((a.z + (a.x * a.y) / (1 + cosa)) * cost, (1 + (-a.z * a.z + -a.y * a.y) / (1 + cosa)) * cost);
	printf("%f, %f, %f\n", cam->rot.x, cam->rot.y, cam->rot.z);
	return (0);
}

int	handle_light(char **line, t_light *light)
{
	const int	len = ptr_array_len(line);

	printf("parse the light\n");
	if (len != 3)
		return (1);
	if (parse_vector3(line[1], &light->pos) == 1
		|| parse_form_range(line[2], &light->brightness, 0, 1) == 1)
	{
		printf(" in the light\n");
		return (1);
	}
	return (0);
}

int	handle_cylinder(char **line, t_shape *cylinder)
{
	const int	len = ptr_array_len(line);

	printf("parse the cylinder\n");
	if (len != 6
		|| parse_vector3(line[1], &cylinder->pos) == 1
		|| parse_vector3_normalised(line[2], &cylinder->axis) == 1
		|| safe_atof(line[3], &cylinder->cylinder.radius) == 1
		|| safe_atof(line[4], &cylinder->cylinder.height) == 1
		|| parse_rgba(line[5], &cylinder->color) == 1)
	{
		printf(" in a cylinder\n");	
		return (1);
	}
	cylinder->get_collision = &cylinder_get_collision;
	cylinder->get_normal = &cylinder_get_normal;
	return (0);// CAP ???
}

int	handle_plane(char **line, t_shape *plane)
{
	const int	len = ptr_array_len(line);

	printf("parse the plan\n");
	if (len != 4
		|| parse_vector3(line[1], &plane->pos) == 1
		|| parse_vector3_normalised(line[2], &plane->plane.normal) == 1
		|| parse_rgba(line[3], &plane->color) == 1)
	{
		printf(" in a plane\n");
		return (1);
	}
	plane->get_collision = &plane_get_collision;
	plane->get_normal = &plane_get_normal;
	return (0);
}

int	handle_sphere(char **line, t_shape *sphere)
{
	const int	len = ptr_array_len(line);

	printf("parse the sphere\n");
	if (len != 4
		|| parse_vector3(line[1], &sphere->pos) == 1
		|| safe_atof(line[2], &sphere->sphere.radius) == 1
		|| parse_rgba(line[3], &sphere->color) == 1)
	{
		printf(" in a sphere\n");
		return (1);
	}
	sphere->get_collision = &sphere_get_collision;
	sphere->get_normal = &sphere_get_normal;
	return (0);
}

int	parse_line(char *line, t_shape_list *list, t_camera *cam, t_light *light)
{
	char		**params;
	static int	nb_shape = 0;

	params = ft_split(line, ' ');
	if (params == 0)
		return (1);
	if ((params[0][0] == 'A' && handle_ambient(params, light) == 1)
		|| (params[0][0] == 'C' && handle_camera(params, cam) == 1)
		|| (params[0][0] == 'L' && handle_light(params, light) == 1)
		|| (params[0][0] == 'c' && handle_cylinder(params, &list->array[nb_shape]) == 1)// CAP ???
		|| (params[0][0] == 'p' && handle_plane(params, &list->array[nb_shape]) == 1)
		|| (params[0][0] == 's' && handle_sphere(params, &list->array[nb_shape]) == 1))
		return (ft_free_split(params), 1);
	if (params[0][0] == 'c' || params[0][0] == 'p' || params[0][0] == 's')
		nb_shape++;
	return (0);
}

int	fill_data_structs(char **lines, t_shape_list *list, t_camera *cam,
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

char	*parse_file(char *filename)
{
	int		fd;
	char	*file;

	if (ft_strchr_last_index(filename, '.') == -1 || ft_strcmp(filename + ft_strchr_last_index(filename, '.'), ".rt") != 0)
	{
		printf("Error\n%s does no end with .rt\n", filename);
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n%s could not be opened\n", filename);
		return (NULL);
	}
	file = read_file(fd);
	close(fd);
	return (file);
}

int	parsing(char *filename, t_shape_list **list, t_camera *cam,
		t_light *light)
{
	char	*file;
	char	**lines;

	file = parse_file(filename);
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
