/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:31:34 by edarnand          #+#    #+#             */
/*   Updated: 2025/06/24 13:58:06 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math_utils.h"
#include "parsing.h"

int	parse_rgba(char *str, t_color *color)
{
	const char	**rgba = (const char **)split_better(str, ',');
	int	r;
	int	g;
	int	b;

	if (rgba == NULL
		|| count_comma(str) != 2
		|| ptr_array_len((char **)rgba) != 3
		|| safe_atoi(rgba[0], &r) == 1 || r < 0 || r > 255
		|| safe_atoi(rgba[1], &g) == 1 || g < 0 || g > 255
		|| safe_atoi(rgba[2], &b) == 1 || b < 0 || b > 255)
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s is not a valid color", str);
		return (free_1_return_1(rgba));
	}
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = 0;
	return (free_1_return_0(rgba));
}

int	parse_form_range(char *str, float *range, float min, float max)
{
	if (safe_atof(str, range) == 1
		|| *range < min || *range > max)
	{
		ft_dprintf(STDERR_FILENO,
			"Error\n%s is not a valid float in range %d %d",
			str, (int)min, (int)max);
		return (1);
	}
	return (0);
}

int	parse_float(char *str, float *f)
{
	if (safe_atof(str, f) == 1)
	{
		ft_dprintf(STDERR_FILENO,
			"Error\n%s is not a valid float", str);
		return (1);
	}
	if (*f <= EPSILON)
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s need to be superior to 0", str);
		return (1);
	}
	return (0);
}

int	verif_len(int len, int target)
{
	if (len != target)
	{
		ft_dprintf(STDERR_FILENO,
			"Error\n%d params needed but you have %d", target, len);
		return (1);
	}
	return (0);
}
