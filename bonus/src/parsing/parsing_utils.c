/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 12:31:34 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/27 10:35:20 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math_utils.h"
#include "minirt.h"
#include <fcntl.h>

int	parse_rgba(char *str, t_color *color)
{
	const char	**rgba = (const char **)ft_split(str, ',');
	const int	len = ptr_array_len((char **)rgba);
	const int	r = color->r;
	const int	g = color->g;
	const int	b = color->b;

	if (len != 3
		|| safe_atoi(rgba[0], (int *)&r) == 1 || r < 0 || r > 255
		|| safe_atoi(rgba[1], (int *)&g) == 1 || g < 0 || g > 255
		|| safe_atoi(rgba[2], (int *)&b) == 1 || b < 0 || b > 255)
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s is not a valid color", str);
		ft_free_split((char **)rgba);
		return (1);
	}
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = 0;
	ft_free_split((char **)rgba);
	return (0);
}

int	parse_form_range(char *str, float *range, float min, float max)
{
	if (safe_atof(str, range) == 1
		|| *range < min || *range > max)
	{
		ft_dprintf(STDERR_FILENO,
			"Error\n%s is not a valid float in range %d %d", str, (int)min, (int)max);
		return (1);
	}
	return (0);
}

int	parse_float(char *str, float *f)
{
	if (safe_atof(str, f) == 1)
	{
		ft_dprintf(STDERR_FILENO, "Error\n%s is not a valid float", str);
		return (1);
	}
	return (0);
}

int	parse_file(char *str, int *fd)
{
	if (ft_strcmp(str, "0") == 0)
	{
		*fd = -1;
		return (0);
	}
	*fd = open(str, O_RDONLY);
	if (*fd == -1)
		return (print_perror_1(ERR_NO_OPEN, str));
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
