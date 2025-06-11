/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:21:34 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/11 14:15:33 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H

# define MATH_UTILS_H

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

//color_utils.c
t_color	color_mult(t_color color1, t_color color2);
t_color	color_scaling(t_color color, float scale);
t_color	color_sum(t_color color1, t_color color2);

//vec_3_scalar_ops.c
t_vec3	scalar_division(t_vec3 vec, float scalar);
t_vec3	scalar_mult(t_vec3 vec, float scalar);

//vec_3_vector_ops.c
t_vec3	cross_product(t_vec3 vec1, t_vec3 vec2);
t_vec3	ortho_proj(t_vec3 projected, t_vec3 line);
t_vec3	vector_mult(t_vec3 term1, t_vec3 term2);
t_vec3	vector_subtraction(t_vec3 minuend, t_vec3 subtrahend);
t_vec3	vector_sum(t_vec3 term1, t_vec3 term2);

//vec_3_to_float.c
float	dot_product(t_vec3 vec1, t_vec3 vec2);
t_vec3	vector_normalization(t_vec3 vec);
float	get_squared_norm(t_vec3 vec);
float	get_norm(t_vec3 vec);
int		vector_equal(t_vec3 vec1, t_vec3 vec2);

#endif //MATH_UTILS_H
