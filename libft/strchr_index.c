/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:29:00 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/20 15:49:36 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int	ft_strchr_index(const char *s, int c)
{
	int	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

int	ft_strchr_last_index(const char *s, int c)
{
	int	i;
	int	len;

	if (s == NULL)
		return (-1);
	len = ft_strlen(s);
	i = len - 1;
	while (i >= 0 && s[i] != 'c')
	{
		if (s[i] == (char)c)
			return (i);
		i--;
	}
	return (-1);
}
