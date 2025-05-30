/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:52:20 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/30 16:04:52 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include "shapes.h"
#include "minirt.h"
#include <math.h>

static void	cylinder_calc_discriminant(t_cylinder_col *data,
	const t_cylinder *cylinder, t_ray ray)
{
	data->origin = vector_sub(cylinder->pos, ray.origin);
	data->d_perp = vector_sub(ray.direction,
			ortho_proj(ray.direction, cylinder->axis));
	data->o_perp = vector_sub(data->origin,
			ortho_proj(data->origin, cylinder->axis));
	data->a = dot_product(data->d_perp, data->d_perp);
	data->h = dot_product(data->o_perp, data->d_perp);
	data->c = dot_product(
			data->o_perp, data->o_perp) - cylinder->radius * cylinder->radius;
}

float	cylinder_get_collision(void *cylinder_void, t_ray ray)
{
	const t_cylinder	*cylinder = (t_cylinder*)cylinder_void;
	t_cylinder_col		data;

	cylinder_calc_discriminant(&data, cylinder, ray);
	data.discriminant = data.h * data.h - data.a * data.c;
	if (data.discriminant < 0)
		return (-1);
	data.discriminant_sqrt = sqrtf(data.discriminant);
	data.t = (data.h - data.discriminant_sqrt) / data.a;
	if (data.t < 0)
	{
		data.t = (data.h + data.discriminant_sqrt) / data.a;
		if (data.t < 0)
			return (-1);
	}
	data.col = vector_sum(ray.origin, scalar_mult(ray.direction, data.t));
	data.len = dot_product(vector_sub(data.col, cylinder->pos), cylinder->axis);
	if (data.len < cylinder->height / 2 && data.len > -cylinder->height / 2)
		return (data.t);
	return (-1);
}

float	cap_up_get_collision(void *cylinder_void, t_ray ray)
{
	const t_cylinder	*cylinder = (t_cylinder*)cylinder_void;
	t_cap_col			data;

	data.dot = dot_product(cylinder->axis, ray.direction);
	if (data.dot == 0)
		return (-1);
	data.cap_pos = vector_sum(cylinder->pos,
			scalar_mult(cylinder->axis, cylinder->height / 2));
	data.origin = vector_sub(ray.origin, data.cap_pos);
	data.intersection = -dot_product(cylinder->axis, data.origin) / data.dot;
	if (data.intersection < 0)
		return (-1);
	data.col = vector_sum(data.origin,
			scalar_mult(ray.direction, data.intersection));
	if (dot_product(data.col, data.col) < cylinder->radius * cylinder->radius)
		return (data.intersection);
	return (-1);
}

float	cap_down_get_collision(void *cylinder_void, t_ray ray)
{
	const t_cylinder	*cylinder = (t_cylinder*)cylinder_void;
	t_cap_col			data;

	data.dot = dot_product(cylinder->axis, ray.direction);
	if (data.dot == 0)
		return (-1);
	data.cap_pos = vector_sum(cylinder->pos,
			scalar_mult(cylinder->axis, cylinder->height / -2));
	data.origin = vector_sub(ray.origin, data.cap_pos);
	data.intersection = -dot_product(cylinder->axis, data.origin) / data.dot;
	if (data.intersection < 0)
		return (-1);
	data.col = vector_sum(data.origin,
			scalar_mult(ray.direction, data.intersection));
	if (dot_product(data.col, data.col) < cylinder->radius * cylinder->radius)
		return (data.intersection);
	return (-1);
}
