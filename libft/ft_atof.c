/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:59:51 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/16 18:29:15 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	protected_atof(const char *s, float *f)
{
	int	i;
	int	count;

	i = 0;
	if (!s || !*s || (*s == '.' && s[1] == 0))
		return (1);
	if (*s == '-' || *s == '+')
		i++;
	if (!s[i--])
		return (1);
	count = 0;
	while (ft_isdigit(s[++i]))
		count++;
	if (s[i] != 0 || count > 10)
	{
		if (count > 10 || s[i] != '.')
			return (1);
		count = 0;
		while (ft_isdigit(s[++i]))
			count++;
		if (count > 10 || s[i] != 0)
			return (1);
	}
	*f = ft_atof(s);
	return (0);
}

float	ft_atof(const char *s)
{
	float	f;
	int		exponent;
	int		i;
	char	sign;

	f = 0;
	i = 0;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(s[i]))
		f = f * 10. + s[i++] - '0';
	if (s[i++] != '.')
		return (f * sign);
	exponent = 10;
	while (ft_isdigit(s[i]))
	{
		f = f + (float)(s[i++] - '0') / exponent;
		exponent *= 10;
	}
	return (f * sign);
}
