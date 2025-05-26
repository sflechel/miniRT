/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:45:54 by sflechel          #+#    #+#             */
/*   Updated: 2025/01/30 12:45:56 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dynamic_array	init_dynamic_array(size_t size)
{
	t_dynamic_array	output;

	output.arr = malloc((size + 1) * sizeof(char *));
	output.arr[size] = 0;
	output.size = 0;
	output.capacity = size;
	return (output);
}

int	push_array(t_dynamic_array *darray, char *elem)
{
	t_dynamic_array	doubled;
	size_t			i;

	i = 0;
	if (darray->capacity - darray->size <= 0)
	{
		doubled = init_dynamic_array(darray->size * 2);
		if (doubled.arr == 0)
			return (1);
		while (i < darray->size)
		{
			doubled.arr[i] = darray->arr[i];
			i++;
		}
		doubled.size = darray->size;
		free(darray->arr);
		*darray = doubled;
	}
	darray->arr[darray->size] = elem;
	darray->size++;
	return (0);
}
