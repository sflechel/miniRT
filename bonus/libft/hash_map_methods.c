/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map_methods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:21:23 by sflechel          #+#    #+#             */
/*   Updated: 2025/05/02 08:26:25 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <strings.h>

int	table_find_nearest_free_spot(t_hash_table *table, char *key)
{
	size_t	i;

	i = table_hash_function(key, table->capacity);
	while (i < table->capacity && table->items[i].key)
	{
		if (ft_strcmp(table->items[i].key, key) == 0)
		{
			table_remove_item(table, key, MODE_DELETE, i);
			break ;
		}
		i++;
	}
	return (i);
}

int	table_insert(t_hash_table *table, char *key, char *value)
{
	size_t		i;
	const int	load = table->size * 100 / table->capacity;

	if (!key)
		return (free_1_return_1(value));
	if (load > 50 && table_resize(table) == 1)
		return (1);
	i = table_find_nearest_free_spot(table, key);
	if (i < table->capacity)
	{
		table->items[i] = (t_ht_item){.key = key, .value = value};
		table->size++;
	}
	else
	{
		if (table_resize(table) == 1)
			return (1);
		table_insert(table, key, value);
	}
	return (0);
}

char	*table_search(t_hash_table *table, const char *key)
{
	size_t	i;

	i = table_hash_function(key, table->capacity);
	while (i < table->capacity && table->items[i].key)
	{
		if (table->items[i].value && ft_strcmp(table->items[i].key, key) == 0)
			return (table->items[i].value);
		i++;
	}
	return (0);
}

void	table_remove_item(t_hash_table *table, char *key,
					t_hash_mode mode, int index)
{
	static char	deleted_item;
	size_t		i;

	if (mode == MODE_DELETE)
	{
		if (table->items[index].key != &deleted_item)
			free(table->items[index].key);
		free(table->items[index].value);
		table->items[index] = (t_ht_item){.key = NULL, .value = NULL};
		return ;
	}
	i = table_hash_function(key, table->capacity);
	while (table->capacity && table->items[i].key)
	{
		if (ft_strcmp(table->items[i].key, key) == 0)
		{
			table_remove_item(table, key, MODE_DELETE, i);
			table->items[i].key = &deleted_item;
		}
		i++;
	}
	if (i < table->capacity)
		table->size--;
}
