/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:21:34 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/05 18:54:01 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H

# define MATH_UTILS_H

# define EPSILON 1e-6f

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_mat_3x3
{
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;
}	t_mat_3x3;

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

//color_utils.c
t_color		color_mult(const t_color color1, const t_color color2);
t_color		color_scaling(const t_color color, const float scale);
t_color		color_sum(const t_color color1, const t_color color2);

//vec_3_scalar_ops.c
t_vec3		scalar_division(const t_vec3 vec, const float scalar);
t_vec3		scalar_mult(const t_vec3 vec, const float scalar);

//vec_3_vector_ops.c
t_vec3		cross_product(const t_vec3 vec1, const t_vec3 vec2);
t_vec3		ortho_proj(const t_vec3 projected, const t_vec3 line);
t_vec3		vector_mult(const t_vec3 term1, const t_vec3 term2);
t_vec3		vector_division(const t_vec3 term1, const t_vec3 term2);
t_vec3		vector_sub(const t_vec3 minuend, const t_vec3 subtrahend);
t_vec3		vector_sum(const t_vec3 term1, const t_vec3 term2);
int			vector_equal(const t_vec3 vec1, const t_vec3 vec2);

//vec_3_to_float.c
float		dot_product(const t_vec3 vec1, const t_vec3 vec2);
t_vec3		vector_normalization(const t_vec3 vec);
float		get_squared_norm(const t_vec3 vec);
float		get_norm(const t_vec3 vec);

//matrix
t_mat_3x3	matrix_mult(const t_mat_3x3 m1, const t_mat_3x3 m2);
t_vec3		matrix_mult_vec3(const t_mat_3x3 m, const t_vec3 vec);
t_mat_3x3	matrix_transpose(const t_mat_3x3 m);

//gradient.c
t_vec3		quadric_get_gradient(const t_vec3	axes);

//rotation.c
void		rotation(t_vec3 *vec, const t_vec3 rot);
void		rotation_x(t_vec3 *vec, const float angle);
void		rotation_y(t_vec3 *vec, const float angle);
void		rotation_z(t_vec3 *vec, const float angle);
t_mat_3x3	axis_angle_to_rotation_matrix(const t_vec3 axis_from, const t_vec3 axis_to);

#endif //MATH_UTILS_H
