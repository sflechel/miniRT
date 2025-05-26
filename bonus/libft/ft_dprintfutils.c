/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintfutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:03:44 by sflechel          #+#    #+#             */
/*   Updated: 2025/01/17 14:03:47 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dputnbrcount(int fd, int n)
{
	unsigned int	buf;
	int				count;

	count = 0;
	if (n < 0)
	{
		buf = -n;
		if (write(fd, "-", 1) == -1)
			return (-1);
	}
	else
		buf = n;
	if (buf >= 10)
	{
		count += ft_dputnbrcount(fd, buf / 10);
		if (count == -1)
			return (-1);
	}
	if (ft_putchar_fd(buf % 10 + '0', fd) != -1)
		count++;
	else
		return (-1);
	if (n < 0)
		count++;
	return (count);
}

int	ft_dputulonglonghex(int fd, uintptr_t n)
{
	char	c;
	int		count;

	count = 0;
	if (n >= 16)
	{
		count += ft_dputulonglonghex(fd, n / 16);
		if (count == -1)
			return (-1);
	}
	c = "0123456789abcdef"[n % 16];
	if (write(fd, &c, 1) != -1)
		count++;
	else
		return (-1);
	return (count);
}

int	ft_dputhexmaj(int fd, unsigned int n)
{
	char	c;
	int		count;

	count = 0;
	if (n >= 16)
	{
		count += ft_dputhexmaj(fd, n / 16);
		if (count == -1)
			return (-1);
	}
	c = "0123456789ABCDEF"[n % 16];
	if (write(fd, &c, 1) != -1)
		count++;
	else
		return (-1);
	return (count);
}

int	ft_dputuint(int fd, unsigned int n)
{
	char	c;
	int		count;

	count = 0;
	if (n >= 10)
	{
		count += ft_dputuint(fd, n / 10);
		if (count == -1)
			return (-1);
	}
	c = n % 10 + '0';
	if (write(fd, &c, 1) != -1)
		count++;
	else
		return (-1);
	return (count);
}
