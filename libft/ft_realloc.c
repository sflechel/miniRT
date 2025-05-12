/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:16:16 by sflechel          #+#    #+#             */
/*   Updated: 2025/01/22 11:16:17 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	void			*output;
	unsigned char	*old_ptr;
	size_t			i;

	i = 0;
	old_ptr = (unsigned char *)ptr;
	output = malloc(size);
	if (output == 0)
		return (free(old_ptr), NULL);
	if (size == 0 && old_ptr != 0)
		return (free(old_ptr), NULL);
	if (old_ptr == 0)
		return (output);
	while (i < old_size && i < size)
	{
		((unsigned char *)output)[i] = old_ptr[i];
		i++;
	}
	free(old_ptr);
	return (output);
}
