/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:51:29 by sflechel          #+#    #+#             */
/*   Updated: 2024/11/07 18:40:36 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*output;

	len = ft_strlen(s);
	output = ft_calloc(len + 1, sizeof(char));
	if (output == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		output[i] = (f)(i, s[i]);
		i++;
	}
	return (output);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		(f)(i, &s[i]);
		i++;
	}
}
