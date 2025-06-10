/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:41:44 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/10 10:18:34 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# define SCREEN_HEIGHT 1444
# define NB_THREAD 100
# define NORMAL_INTENSITY 0.5
# define TEXTURE_SCALE 256

# define M_PI 3.14159265358979323846

# include "shapes.h"

typedef struct s_ray	t_ray;

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

struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
};

typedef struct s_data
{
	t_light_list	*lights;
	t_plane_list	*planes;
	t_sphere_list	*spheres;
	t_cylinder_list	*cylinders;
	t_hyper_list	*hypers;
}	t_data;

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

typedef struct s_thread_data
{
	t_vec3		delta_u;
	t_vec3		delta_v;
	t_vec3		pixel;
	int			start;
	int			stop;
	t_camera	*cam;
	t_data		*lists;
	t_mlx		*mlx;
}	t_thread_data;

typedef enum e_error
{
	ERR_INVALID_UNIQUES,
	ERR_INVALID_ID,
	ERR_INVALID_EXTENSION,
	ERR_NO_OPEN,
	ERR_XPM,
	ERR_INIT_MLX,
	ERR_INIT_WINDOW,
	ERR_INIT_IMG,
	ERR_INVALID_NB_FILES,
	ERR_OPEN_FAIL
}	t_error;

//camera.c
void	update_camera(t_camera *cam);

//scanning.h
void	launch_thread(const t_camera *cam, const t_data *lists,
			const t_mlx *mlx);

//raytracing.h
t_color	cast_ray(const t_ray ray, const t_data *lists);

//camera.c
void	update_camera(t_camera *cam);
void	init_camera(t_camera *cam, t_vec3 *cam_axis, t_mlx *mlx);

//errors.c
int		print_error_1(t_error id);
void	*print_strerror_null(t_error id, char *str);

//main.c
int		free_lists(t_data *lists, t_mlx *mlx);

#endif //MINIRT_H
