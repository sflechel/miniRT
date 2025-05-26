/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:41:44 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/26 15:13:46 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

# include "math_utils.h"
# include "shapes.h"

typedef struct s_light
{
	t_color	ambient;
	t_vec3	pos;
	float	brightness;
}	t_light;

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
	ERR_INVALID_NB_FILES
}	t_error;

//camera.c
void	update_camera(t_camera *cam);

//scanning.h
void	scan_viewport(t_camera *camera, t_data *shapes,
			t_light light, t_mlx *mlx);

//raytracing.h
t_color	cast_ray(t_ray ray, t_data *shapes, t_light light);

//rotation.c
void	rotation(t_vec3 *vec, t_vec3 rot);
void	rotation_x(t_vec3 *vec, float angle);
void	rotation_y(t_vec3 *vec, float angle);
void	rotation_z(t_vec3 *vec, float angle);

//camera.c
void	update_camera(t_camera *cam);
void	init_camera(t_camera *cam, t_vec3 *cam_axis);

//errors.c
int		print_error_1(t_error id);
void	*print_strerror_null(t_error id, char *str);

#endif //MINIRT_H
