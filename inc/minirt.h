/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:41:44 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/12 13:15:16 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

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
		char	a;
		char	r;
		char	g;
		char	b;
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

typedef struct s_sphere
{
	t_shape	shape;
	float	radius;
}	t_sphere;

#endif // !MINIRT_H
