/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloced.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:56:43 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/02 12:31:15 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (nmemb * size < 0)
		return (0);
	if (nmemb * size > INT_MAX)
		return (0);
	mem = malloc(nmemb * size);
	if (mem <= 0)
		return (0);
	ft_bzero(mem, nmemb * size);
	return (mem);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dup;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	dup = ft_calloc(len + 1, sizeof(char));
	if (dup <= 0)
		return (0);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	strlen;
	char	*sub;
	size_t	i;

	strlen = ft_strlen(s);
	if (start <= strlen)
		strlen -= start;
	else
		return (ft_calloc(1, sizeof(char)));
	if (strlen >= len)
		strlen = len;
	sub = ft_calloc(strlen + 1, sizeof(char));
	if (sub <= 0)
		return (0);
	i = 0;
	while (i < strlen)
	{
		sub[i] = s[i + start];
		i++;
	}
	return (sub);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = ft_calloc(len, sizeof(char));
	if (joined <= 0)
		return (0);
	ft_strlcat(joined, s1, len);
	ft_strlcat(joined, s2, len);
	return (joined);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		len;
	char	*trimmed;

	i = 0;
	while ((ft_isincharset(s1[i], set) == 1) && s1[i])
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while ((ft_isincharset(s1[i], set) == 1) && s1[i])
		i--;
	len = i - start + 1;
	if (len < 0)
		len = 0;
	trimmed = ft_calloc(len + 1, sizeof(char));
	if (trimmed <= 0)
		return (0);
	i = 0;
	while (i < len)
	{
		trimmed[i] = s1[i + start];
		i++;
	}
	return (trimmed);
}
