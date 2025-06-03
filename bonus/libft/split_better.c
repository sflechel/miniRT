/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_better.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:20:37 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/03 17:09:23 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_split_size(const char *str, char c, int *word_counter)
{
	int	i;
	int	c_counter;

	*word_counter = 0;
	c_counter = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
		{
			i++;
			c_counter++;
		}
		if (str[i])
			(*word_counter)++;
		while (str[i] && str[i] != c)
			i++;
	}
	return ((*word_counter + 1) * (sizeof(char *))
		+ (ft_strlen(str) - c_counter + *word_counter) * sizeof(char));
}

static int	ft_worddup(char *dest, const char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != c)
		i++;
	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i + 1);
}

static char	**ft_realsplit(char const *s, char c, char **strs, int word_counter)
{
	void	*pos;
	int		i;

	i = 0;
	pos = (void *)strs + (word_counter + 1) * sizeof(char *);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s != '\0')
		{
			strs[i] = pos;
			pos += ft_worddup(strs[i], s, c);
		}
		while (*s != c && *s)
			s++;
		i++;
	}
	return (strs);
}

char	**split_better(char const *s, char c)
{
	char	**strs;
	int		word_counter;

	if (!s)
		return (0);
	if (!*s)
		return (ft_calloc(1, sizeof(char *)));
	strs = malloc(ft_split_size(s, c, &word_counter));
	if (strs == 0)
		return (0);
	strs = ft_realsplit(s, c, strs, word_counter);
	strs[word_counter] = 0;
	return (strs);
}
