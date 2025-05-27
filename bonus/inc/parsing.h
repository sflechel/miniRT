/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:02:03 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/27 10:39:17 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"

# define READ_SIZE 100

typedef enum e_id
{
	ID_AMBIENT = 0,
	ID_CAMERA = 1,
	ID_LIGHT = 2,
	ID_CYLINDER,
	ID_SPHERE,
	ID_PLANE,
	ID_ERROR
}	t_id;

//parsing.c
int		parsing(char *filename, t_data *list, t_camera *cam,
			t_light_list **lights);

//parse_file_and_line
char	*open_and_read_file(char *filename);
int		parse_line(char *line, t_data *list, t_camera *cam, t_light_list *lights);

//parse_shape
int		handle_cylinder(char **line, t_cylinder_list *list);
int		handle_plane(char **line, t_plane_list *list);
int		handle_sphere(char **line, t_sphere_list *list);

//parse_unique
int		handle_ambient(char **line, t_light_list *lights);
int		handle_camera(char **line, t_camera *cam);
int		handle_light(char **line, t_light_list *lights);

//parsing_utils
int		parse_rgba(char *str, t_color *color);
int		parse_form_range(char *str, float *range, float min, float max);
int		parse_float(char *str, float *f);
int		verif_len(int len, int target);
int		parse_file(char *str, int *fd);

//parsing_utils_vector
int		parse_vector3(char *str, t_vec3 *vec);
int		parse_vector3_normalised(char *str, t_vec3 *vec);

#endif
