/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:16:16 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/19 16:14:55 by edarnand         ###   ########.fr       */
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
		return (free_1_return_null(old_ptr));
	if (size == 0 && old_ptr != 0)
		return (free_1_return_null(old_ptr));
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
