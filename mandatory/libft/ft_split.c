/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:15:07 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/02 11:47:22 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(const char *str, char c)
{
	int	counter;

	counter = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			counter++;
		while (*str && *str != c)
			str++;
	}
	return (counter);
}

static char	*ft_worddup(char *dest, const char *src, char c)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != c)
		i++;
	dest = ft_calloc(i + 1, sizeof(char));
	if (dest == 0)
		return (0);
	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_free_split(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return (0);
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}

static char	**ft_realsplit(char const *s, char c, char **strs)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != '\0')
		{
			strs[i] = ft_worddup(strs[i], s, c);
			if (strs[i] == 0)
			{
				ft_free_split(strs);
				return (0);
			}
		}
		while (*s != c && *s)
			s++;
		i++;
	}
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;

	if (!s)
		return (0);
	if (!*s)
		return (ft_calloc(1, sizeof(char *)));
	strs = ft_calloc(ft_countwords(s, c) + 1, sizeof(char *));
	if (strs == 0)
		return (0);
	strs = ft_realsplit(s, c, strs);
	if (strs == 0)
		return (0);
	return (strs);
}
