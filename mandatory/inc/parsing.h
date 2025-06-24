/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:02:03 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/24 16:25:33 by edarnand         ###   ########.fr       */
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
	ID_CORRECT,
	ID_CYLINDER,
	ID_ERROR
}	t_id;

int		parsing(char *filename, t_shape_list **list, t_camera *cam,
			t_light *light);

//parse_file_and_line
char	*open_and_read_file(char *filename);
int		parse_line(char *line, t_shape_list *list, t_camera *cam,
			t_light *light);

//parse_shape
int		handle_cylinder(char **line, t_shape_list *shapes, int index);
int		handle_plane(char **line, t_shape *plane);
int		handle_sphere(char **line, t_shape *sphere);

//parse_unique
int		handle_ambient(char **line, t_light *light);
int		handle_camera(char **line, t_camera *cam);
int		handle_light(char **line, t_light *light);

//parsing_utils
int		parse_rgba(char *str, t_color *color);
int		parse_form_range(char *str, float *range, float min, float max);
int		parse_float(char *str, float *f);
int		verif_len(int len, int target);

//parsing_utils_vector
int		parse_vector3(char *str, t_vec3 *vec);
int		parse_vector3_normalised(char *str, t_vec3 *vec);
int		count_comma(char *str);

#endif
