/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:41:44 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/13 10:20:05 by sflechel         ###   ########.fr       */
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
		unsigned char	a;
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;
	};
	int	rgba;
}	t_color;

typedef enum e_type
{
	SPHERE
}	t_type;

typedef struct s_shape	t_shape;

struct s_shape
{
	t_type	type;
	t_vec3	pos;
	t_vec3	rot;
	t_color	color;
	int		(*get_collision)(t_shape *shape, t_vec3 *ray, t_vec3 *camera_pos);
};

typedef struct s_shape_list
{
	// int		sizes[3];
	int		nb_shapes;
	t_shape	array[];
}	t_shape_list;

typedef struct s_sphere
{
	t_shape	shape;
	float	radius;
}	t_sphere;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

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

#endif // !MINIRT_H
