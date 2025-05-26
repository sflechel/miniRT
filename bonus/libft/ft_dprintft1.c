/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintft1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:03:19 by sflechel          #+#    #+#             */
/*   Updated: 2025/01/17 14:03:24 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintchar(int fd, char c)
{
	return (write(fd, &c, 1));
}

int	ft_dprintstr(int fd, char *str)
{
	int	byte_written;
	int	len;

	if (str == 0)
	{
		if (write(fd, "(null)", 6) != 6)
			return (-1);
		else
			return (6);
	}
	len = ft_strlen(str);
	byte_written = write(fd, str, len);
	if (byte_written < len)
		return (-1);
	return (byte_written);
}

int	ft_dprintvoidptr(int fd, uintptr_t ptr)
{
	if (ptr == 0)
	{
		if (write(fd, "(nil)", 5) != 5)
			return (-1);
		else
			return (5);
	}
	if (write(fd, "0x", 2) != 2)
		return (-1);
	return (ft_dputulonglonghex(fd, ptr) + 2);
}
