/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_vector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:35:42 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/24 16:24:49 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math_utils.h"
#include <unistd.h>

int	count_comma(char *str)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			comma_count++;
		i++;
	}
	return (comma_count);
}

int	parse_vector3(char *str, t_vec3 *vec)
{
	char	**vector;

	vector = split_better(str, ',');
	if (vector == NULL
		|| ptr_array_len(vector) != 3
		|| count_comma(str) != 2
		|| safe_atof(vector[0], &vec->x) == 1
		|| safe_atof(vector[1], &vec->y) == 1
		|| safe_atof(vector[2], &vec->z) == 1)
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s is not a valid vector 3", str);
		return (free_1_return_1(vector));
	}
	return (free_1_return_0(vector));
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
