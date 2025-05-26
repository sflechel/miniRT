/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:49:47 by sflechel          #+#    #+#             */
/*   Updated: 2025/01/27 09:49:50 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_repeat_character(char *str)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		j = i + 1;
		while (str[i] != str[j] && (str[j]))
		{
			j++;
		}
		if (str[i] == str[j])
			return (0);
		i++;
	}
	return (1);
}

int	ft_base_is_correct(char *base)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(base);
	if (len <= 1)
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || base[i] == ' ')
			return (0);
		i++;
	}
	if (ft_repeat_character(base) == 0)
		return (0);
	return (1);
}

int	ft_pos_in_base(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	long int	nb;
	int			sign;
	int			lenbase;

	nb = 0;
	sign = 1;
	if (ft_base_is_correct(base) == 0)
		return (0);
	lenbase = ft_strlen(base);
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_pos_in_base(base, *str) > -1)
	{
		nb = nb * lenbase + ft_pos_in_base(base, *str);
		if ((nb > 2147483647 && sign != -1) || nb > 2147483648)
			return (0);
		str++;
	}
	return (sign * nb);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		num = num * 10 + nptr[i] - '0';
		i++;
	}
	return (num * sign);
}
