/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:55:22 by sflechel          #+#    #+#             */
/*   Updated: 2025/04/28 16:25:19 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s == 0)
		return (0);
	if (s[0] == 0)
		return (0);
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (size <= 0)
		return (srclen);
	while (src[i] && (i + 1 < size))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (srclen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;

	len_dest = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	if (size < 1)
		return (len_src);
	while (src[i] != '\0' && i + len_dest + 1 < size)
	{
		dst[len_dest + i] = src[i];
		i++;
	}
	dst[len_dest + i] = '\0';
	if (size < len_dest)
		return (len_src + size);
	else
		return (len_dest + len_src);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (str1[i] && (str1[i] == str2[i]) && (i < n - 1))
		i++;
	return (str1[i] - str2[i]);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	lenlittle;
	size_t	lenbig;
	size_t	i;
	size_t	j;

	if (*little == 0)
		return ((char *) big);
	lenlittle = ft_strlen(little);
	lenbig = ft_strlen(big);
	i = 0;
	while ((i + lenlittle <= lenbig) && i < len && i < lenbig)
	{
		j = 0;
		while (little[j] == big[i + j] && i + j < len && i + j < lenbig)
			j++;
		if (j == lenlittle)
			return ((char *) &big[i]);
		i++;
	}
	return (0);
}
