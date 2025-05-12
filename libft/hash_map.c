/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:45:20 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/01 18:31:46 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

t_hash_table	*table_alloc(int capacity)
{
	t_hash_table	*table;

	table = malloc(sizeof(t_hash_table));
	if (table == 0)
		return (0);
	*table = (t_hash_table){.size = 0, .capacity = capacity};
	table->items = ft_calloc(capacity, sizeof(t_ht_item));
	if (table->items == 0)
	{
		free(table);
		return (0);
	}
	return (table);
}

// void	table_delete_item(t_hash_table *table, int index)
// {
// 	free(table->items[index].key);
// 	free(table->items[index].value);
// 	table->items[index] = (t_ht_item){.key = NULL, .value = NULL};
// }

void	table_delete_table(t_hash_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->capacity)
	{
		if (table->items[i].key != 0)
			table_remove_item(table, 0, MODE_DELETE, i);
		i++;
	}
	free(table->items);
	free(table);
}

int	table_insert_for_resize(t_hash_table *table, char *key, char *value)
{
	size_t		i;

	i = table_hash_function(key, table->capacity);
	while (i < table->capacity && table->items[i].key)
		i++;
	if (i < table->capacity)
	{
		table->items[i] = (t_ht_item){.key = key, .value = value};
		table->size++;
	}
	return (0);
}

int	table_resize(t_hash_table *table)
{
	t_hash_table	*new_table;
	t_ht_item		*tmp_items;
	size_t			tmp_capacity;
	size_t			i;

	new_table = table_alloc(table->capacity * 2);
	if (new_table == 0)
		return (1);
	i = 0;
	while (i < table->capacity)
	{
		if (table->items[i].key)
			table_insert(new_table, table->items[i].key, table->items[i].value);
		i++;
	}
	tmp_items = table->items;
	table->items = new_table->items;
	new_table->items = tmp_items;
	table->size = new_table->size;
	tmp_capacity = table->capacity;
	table->capacity = new_table->capacity;
	new_table->capacity = tmp_capacity;
	free(new_table->items);
	free(new_table);
	return (0);
}
