/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:35:42 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/30 16:40:50 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math_utils.h"

int	parse_vector3(char *str, t_vec3 *vec)
{
	const char	**vector = (const char **)ft_split(str, ',');
	const int	len = ptr_array_len((char **)vector);

	if (len != 3
		|| safe_atof(vector[0], &vec->x) == 1
		|| safe_atof(vector[1], &vec->y) == 1
		|| safe_atof(vector[2], &vec->z) == 1)
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s is not a valid vector 3", str);
		ft_free_split((char **)vector);
		return (1);
	}
	ft_free_split((char **)vector);
	return (0);
}

int	parse_vector3_normalised(char *str, t_vec3 *vec)
{
	if (parse_vector3(str, vec) == 1)
		return (1);
	else if (get_norm(*vec) != 1)
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s cant be normalised", str);
		return (1);
	}
	return (0);
}
