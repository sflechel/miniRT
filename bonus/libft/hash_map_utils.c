/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:28:48 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/01 18:31:50 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	power(int nb, int exponent)
{
	if (exponent < 0)
		return (0);
	if (exponent <= 1)
		return (nb);
	return (power(nb * nb, exponent - 1));
}

int	table_hash_function(const char *key, const int len_table)
{
	long long int	hash;
	int				prime_signature;
	int				len_key;
	int				i;

	prime_signature = 163;
	len_key = ft_strlen(key);
	hash = 0;
	i = 0;
	while (i < len_key)
	{
		hash += power(prime_signature, len_key - i + 1) * key[i];
		hash = hash % (len_table - 1);
		i++;
	}
	return ((int)hash);
}

void	*table_delete_return_null(t_hash_table *table)
{
	table_delete_table(table);
	return (0);
}

void	print_hash_table(t_hash_table *table)
{
	size_t	i;

	printf("size: %zu, capacity: %zu\n", table->size, table->capacity);
	i = 0;
	while (i < table->capacity)
	{
		if (table->items[i].key == 0)
			printf("%zu: no value  \n", i);
		else if (table->items[i].value == 0)
			printf("%zu: empty/removed  \n", i);
		else
			printf("%zu: ,key: %s, value: %s\n", i,
				table->items[i].key, table->items[i].value);
		i++;
	}
}
