/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:02:46 by sflechel          #+#    #+#             */
/*   Updated: 2025/01/17 14:02:50 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printarg(int fd, char print, va_list ptr)
{
	if (print == 'c')
		return (ft_dprintchar(fd, va_arg(ptr, int)));
	if (print == 's')
		return (ft_dprintstr(fd, va_arg(ptr, char *)));
	if (print == 'p')
		return (ft_dprintvoidptr(fd, va_arg(ptr, uintptr_t)));
	if (print == 'd' || print == 'i')
		return (ft_dputnbrcount(fd, va_arg(ptr, int)));
	if (print == 'u')
		return (ft_dputuint(fd, va_arg(ptr, unsigned int)));
	if (print == 'x')
		return (ft_dputulonglonghex(fd, va_arg(ptr, unsigned int)));
	if (print == 'X')
		return (ft_dputhexmaj(fd, va_arg(ptr, unsigned int)));
	if (print == '%')
		return (ft_dprintchar(fd, '%'));
	return (-1);
}

static int	ft_print(int fd, const char *print, va_list ptr)
{
	int	byte_written;
	int	nbrchar;

	nbrchar = 0;
	while (*print)
	{
		if (*print == '%')
		{
			print++;
			byte_written = ft_printarg(fd, *print, ptr);
			if (byte_written == -1)
				return (-1);
			nbrchar += byte_written;
		}
		else
		{
			if (write(fd, print, 1) == -1)
				return (-1);
			nbrchar++;
		}
		print++;
	}
	return (nbrchar);
}

int	ft_dprintf(int fd, const char *print, ...)
{
	va_list	ptr;
	int		nbrchar;

	if (print == 0)
		return (-1);
	va_start(ptr, print);
	nbrchar = ft_print(fd, print, ptr);
	va_end(ptr);
	return (nbrchar);
}

int	ft_printf(const char *print, ...)
{
	va_list	ptr;
	int		nbrchar;

	if (print == 0)
		return (-1);
	va_start(ptr, print);
	nbrchar = ft_print(1, print, ptr);
	va_end(ptr);
	return (nbrchar);
}
