/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:44:24 by sflechel          #+#    #+#             */
/*   Updated: 2024/11/07 10:45:08 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_create_string(int n)
{
	int				order;
	unsigned int	buff;
	char			*output;

	order = 0;
	buff = 0;
	if (n < 0)
	{
		order++;
		buff = -n;
	}
	else
		buff = n;
	while (buff >= 10)
	{
		buff = buff / 10;
		order++;
	}
	order++;
	output = ft_calloc(order + 1, sizeof(char));
	if (output <= 0)
		return (0);
	output[0] = order;
	return (output);
}

static void	nbr_to_string(char *s, int n, int order)
{
	char			c;
	unsigned int	buff;

	order--;
	buff = 0;
	if (n < 0)
	{
		s[0] = '-';
		buff = -n;
	}
	else
		buff = n;
	c = '0' + buff % 10;
	if (buff >= 10)
		nbr_to_string(s, buff / 10, order);
	s[order] = c;
}

char	*ft_itoa(int n)
{
	int		order;
	char	*output;

	output = ft_create_string(n);
	if (output <= 0)
		return (0);
	order = output[0];
	nbr_to_string(output, n, order);
	return (output);
}
