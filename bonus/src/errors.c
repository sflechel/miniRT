/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:06:11 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/28 13:18:57 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include <stdio.h>
#include <unistd.h>

int	print_error_1(t_error id)
{
	const int	e = STDERR_FILENO;

	ft_dprintf(e, "Error\n");
	if (id == ERR_INVALID_UNIQUES)
		ft_dprintf(e,
			"One cam, one ambiante, and at least one light nedded\n");
	else if (id == ERR_INVALID_ID)
		ft_dprintf(e, "Invalid id\n");
	else if (id == ERR_INIT_MLX)
		ft_dprintf(e, "Minilibx failed to initialize\n");
	else if (id == ERR_INIT_WINDOW)
		ft_dprintf(e, "Window failed to initialize\n");
	else if (id == ERR_INIT_IMG)
		ft_dprintf(e, "Image failed to initialize\n");
	else if (id == ERR_INVALID_NB_FILES)
		ft_dprintf(e, "Incorrect amount of files\n");
	return (1);
}

void	*print_strerror_null(t_error id, char *str)
{
	const int	e = STDERR_FILENO;

	ft_dprintf(e, "Error\n");
	if (id == ERR_INVALID_EXTENSION)
		ft_dprintf(e, "%s must end in .rt\n", str);
	else if (id == ERR_NO_OPEN)
		ft_dprintf(e, "%s could not be opened\n", str);
	return (0);
}

int	print_perror_1(t_error id, char *str)
{
	const int	e = STDERR_FILENO;

	ft_dprintf(e, "Error\n");
	if (id == ERR_OPEN_FAIL)
		perror(str);
	return (0);
}
