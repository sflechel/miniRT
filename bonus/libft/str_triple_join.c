/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_triple_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:18:58 by sflechel          #+#    #+#             */
/*   Updated: 2025/04/25 15:47:44 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_triple_join(char const *s1, char const *s2, char const *s3)
{
	char	*joined;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	joined = ft_calloc(len, sizeof(char));
	if (joined <= 0)
		return (0);
	ft_strlcat(joined, s1, len);
	ft_strlcat(joined, s2, len);
	ft_strlcat(joined, s3, len);
	return (joined);
}
