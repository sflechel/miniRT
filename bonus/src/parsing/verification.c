/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:07:57 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/10 10:08:50 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"

int	verif_texture_size(t_image *color, t_image *bump)
{
	if (color == 0 || bump == 0)
		return (0);
	if (color->height != bump->height || color->width != bump->width)
	{
		ft_dprintf(STDERR_FILENO,
			"Error\nBoth textures must be of the same size");
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
