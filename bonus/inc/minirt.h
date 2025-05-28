/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:41:44 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/28 13:35:52 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# define SCREEN_HEIGHT 480

# include "math_utils.h"
# include "shapes.h"

typedef struct s_light
{
	t_vec3	pos;
	t_color	color;
}	t_light;

typedef struct s_light_list
{
	t_color	ambient;
	int		nb_lights;
	t_light	lights[];
}	t_light_list;

typedef struct s_data
{
	t_light_list	*lights;
	t_plane_list	*planes;
	t_sphere_list	*spheres;
	t_cylinder_list	*cylinders;
	t_hyper_list	*hypers;
}	t_data;

struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
};

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	rot;
	t_vec3	focal_length;
	float	vertical_fov;
	int		img_width;
	int		img_heigth;
	float	viewport_heigth;
	float	viewport_width;
	t_vec3	viewport_u;
	t_vec3	viewport_v;
}	t_camera;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len_line;
	int		height;
	int		width;
	int		endian;
}	t_image;

typedef enum e_end
{
	DONT_END,
	END
}	t_end;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	t_image	img;
	t_end	end;
}	t_mlx;

typedef enum e_error
{
	ERR_INVALID_UNIQUES,
	ERR_INVALID_ID,
	ERR_INVALID_EXTENSION,
	ERR_NO_OPEN,
	ERR_INIT_MLX,
	ERR_INIT_WINDOW,
	ERR_INIT_IMG,
	ERR_INVALID_NB_FILES,
	ERR_OPEN_FAIL
}	t_error;

//camera.c
void	update_camera(t_camera *cam);

//scanning.h
void	scan_viewport(t_camera *camera, t_data *lists, t_mlx *mlx);

//raytracing.h
t_color	cast_ray(t_ray ray, t_data *lists);

//rotation.c
void	rotation(t_vec3 *vec, t_vec3 rot);
void	rotation_x(t_vec3 *vec, float angle);
void	rotation_y(t_vec3 *vec, float angle);
void	rotation_z(t_vec3 *vec, float angle);

//camera.c
void	update_camera(t_camera *cam);
void	init_camera(t_camera *cam, t_vec3 *cam_axis, t_mlx *mlx);

//errors.c
int		print_error_1(t_error id);
void	*print_strerror_null(t_error id, char *str);
int		print_perror_1(t_error id, char *str);

#endif //MINIRT_H
