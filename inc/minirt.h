/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:41:44 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/13 12:01:14 by sflechel         ###   ########.fr       */
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

struct s_shape
{
	t_type	type;
	t_vec3	pos;
	t_vec3	rot;
	t_color	color;
	float	(*get_collision)(t_shape *shape, t_ray ray);
	union
	{
		t_sphere	sphere;
	};
};

typedef struct s_shape_list
{
	// int		sizes[3];
	int		nb_shapes;
	t_shape	array[];
}	t_shape_list;

typedef struct s_camera
{
	t_vec3	pos;
	float	focal_length;
	int		img_width;
	int		img_heigth;
	float	viewport_heigth;
	float	viewport_width;
}	t_camera;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len_line;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	t_img	img;
}	t_mlx;

//scanning.h
void	scan_viewport(t_camera *camera, t_shape_list *shapes, t_mlx *mlx);

//raytracing.h
t_color	cast_ray(t_ray ray, t_shape_list *shapes);

//collision.c
float	sphere_get_collision(t_shape *shape, t_ray ray);

//hooks.c
void	handle_hooks(t_mlx *mlx);

//color_utils.c
t_color	color_scaling(t_color color, float scale);
t_color	color_sum(t_color color1, t_color color2);

//vec_3_scalar_ops.c
t_vec3	scalar_division(t_vec3 vec, float scalar);
t_vec3	scalar_multiplication(t_vec3 vec, float scalar);

//vec_3_vector_ops.c
float	dot_product(t_vec3 vec1, t_vec3 vec2);
float	get_squared_magnitude(t_vec3 vec);
t_vec3	vector_normalization(t_vec3 vec);
t_vec3	vector_subtraction(t_vec3 minuend, t_vec3 subtrahend);
t_vec3	vector_sum(t_vec3 term1, t_vec3 term2);

#endif // !MINIRT_H
