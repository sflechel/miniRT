/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:40:03 by sflechel          #+#    #+#             */
/*   Updated: 2025/04/25 16:31:52 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	dup = ft_calloc(n + 1, sizeof(char));
	if (dup <= 0)
		return (0);
	if (n < len)
		ft_strlcpy(dup, s, n + 1);
	else
		ft_strlcpy(dup, s, len + 1);
	return (dup);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (str1[i] && (str1[i] == str2[i]))
		i++;
	return (str1[i] - str2[i]);
}

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	return (c);
}

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 'a');
	return (c);
}

char	*strjoin_and_free_s1(char *s1, char const *s2)
{
	char	*joined;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = ft_calloc(len, sizeof(char));
	if (joined <= 0)
	{
		free(s1);
		return (0);
	}
	ft_strlcat(joined, s1, len);
	free(s1);
	ft_strlcat(joined, s2, len);
	return (joined);
}
