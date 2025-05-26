/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:52:08 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/01 15:29:31 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	safe_atoi(const char *nptr, int *num)
{
	int			i;
	int			sign;
	long long	buf;

	if (!nptr)
		return (1);
	i = 0;
	sign = 1;
	buf = 0;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i++] == '-')
			sign = -1;
	}
	if (!ft_isdigit(nptr[i]))
		return (1);
	while (ft_isdigit(nptr[i]))
		buf = buf * 10 + nptr[i++] - '0';
	if (nptr[i])
		return (1);
	buf *= sign;
	if (buf > INT_MAX || buf < INT_MIN)
		return (1);
	*num = buf;
	return (0);
}
