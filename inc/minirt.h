/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:41:44 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/23 18:38:11 by edarnand         ###   ########.fr       */
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

//camera.c
void	update_camera(t_camera *cam);

//scanning.h
void	scan_viewport(t_camera *camera, t_shape_list *shapes,
			t_light light, t_mlx *mlx);

//raytracing.h
t_color	cast_ray(t_ray ray, t_shape_list *shapes, t_light light);

//rotation.c
void	rotation(t_vec3 *vec, t_vec3 rot);
void	rotation_x(t_vec3 *vec, float angle);
void	rotation_y(t_vec3 *vec, float angle);
void	rotation_z(t_vec3 *vec, float angle);

//camera.c
void	update_camera(t_camera *cam);
void	init_camera(t_camera *cam, t_vec3 *cam_axis);

#endif //MINIRT_H
