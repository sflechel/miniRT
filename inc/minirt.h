/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:41:44 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/16 15:29:48 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

extern const float		g_aspect_ratio;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef union u_color
{
	struct
	{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	};
	int	rgba;
}	t_color;

typedef enum e_type
{
	SPHERE
}	t_type;

typedef struct s_light
{
	float	ambient;
	t_color	ambient_color;
	t_vec3	pos;
	float	brightness;
}	t_light;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_shape	t_shape;

typedef struct s_sphere
{
	float	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	normal;
}	t_plane;

typedef struct s_cylinder
{
	float	radius;
	float	height;
}	t_cylinder;

typedef struct s_disk
{
	float	radius;
	t_vec3	normal;
}	t_disk;

struct s_shape
{
	t_type	type;
	t_vec3	pos;
	t_vec3	axis;
	t_color	color;
	float	(*get_collision)(t_shape *shape, t_ray ray);
	t_vec3	(*get_normal)(t_shape * shape, t_vec3 col);
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_disk		disk;
	};
};

typedef struct s_shape_list
{
	int		nb_shapes;
	t_shape	array[];
}	t_shape_list;

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

typedef struct s_hook_data
{
	t_mlx		*mlx;
	t_camera	*cam;
}	t_hook_data;

//camera.c
void	update_camera(t_camera *cam);

//scanning.h
void	scan_viewport(t_camera *camera, t_shape_list *shapes, t_light light, t_mlx *mlx);

//raytracing.h
t_color	cast_ray(t_ray ray, t_shape_list *shapes, t_light light);

//collision.c
float	get_closest_collision(t_shape_list *shapes, t_ray ray, int *col_index);
int		there_is_collision(t_shape_list *shapes, t_ray ray);
float	disk_get_collision(t_shape *shape, t_ray ray);
float	cylinder_get_collision(t_shape *shape, t_ray ray);
float	sphere_get_collision(t_shape *shape, t_ray ray);
float	plane_get_collision(t_shape *shape, t_ray ray);

//normals.c
t_vec3	disk_get_normal(t_shape *shape, t_vec3 col);
t_vec3	cylinder_get_normal(t_shape *shape, t_vec3 col);
t_vec3	sphere_get_normal(t_shape *shape, t_vec3 col);
t_vec3	plane_get_normal(t_shape *shape, t_vec3 col);

//hooks.c
void	handle_hooks(t_hook_data *data);

//color_utils.c
t_color	color_scaling(t_color color, float scale);
t_color	color_sum(t_color color1, t_color color2);

//vec_3_scalar_ops.c
t_vec3	scalar_division(t_vec3 vec, float scalar);
t_vec3	scalar_mult(t_vec3 vec, float scalar);

//vec_3_vector_ops.c
float	dot_product(t_vec3 vec1, t_vec3 vec2);
float	get_squared_magnitude(t_vec3 vec);
t_vec3	ortho_proj(t_vec3 projected, t_vec3 line);
t_vec3	vector_normalization(t_vec3 vec);
t_vec3	vector_mult(t_vec3 term1, t_vec3 term2);
t_vec3	vector_subtraction(t_vec3 minuend, t_vec3 subtrahend);
t_vec3	vector_sum(t_vec3 term1, t_vec3 term2);

//rotation.c
void	rotation(t_vec3 *vec, t_vec3 rot);
void	rotation_x(t_vec3 *vec, float angle);
void	rotation_y(t_vec3 *vec, float angle);
void	rotation_z(t_vec3 *vec, float angle);

//constructor.c
void	sphere_constructor(t_vec3 pos, t_vec3 axis, t_color color, float radius, t_shape *shape);
void	disk_constructor(t_vec3 pos, t_vec3 axis, t_color color, t_vec3 normal, float radius, t_shape *shape);
void	plane_constructor(t_vec3 pos, t_vec3 axis, t_color color, t_vec3 normal, t_shape *shape);
void	cylinder_constructor(t_vec3 pos, t_vec3 axis, t_color color, float radius, float height, t_shape *shape);

//camera.c
void	update_camera(t_camera *cam);
void	init_camera(t_camera *cam);

#endif // !MINIRT_H
