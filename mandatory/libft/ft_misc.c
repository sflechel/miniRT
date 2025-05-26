/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:22:28 by sflechel          #+#    #+#             */
/*   Updated: 2024/11/07 17:30:37 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		i++;
	}
	if ((char) c == '\0')
		return ((char *) &s[i]);
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	best;

	best = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			best = i;
		i++;
	}
	if ((char) c == 0)
		return ((char *) &s[i]);
	if (best != -1)
		return ((char *) &s[best]);
	return (0);
}

int	ft_isincharset(char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ptr_array_len(char **ptr_array)
{
	int	len;

	len = 0;
	if (ptr_array == 0)
		return (0);
	while (ptr_array[len])
		len++;
	return (len);
}
