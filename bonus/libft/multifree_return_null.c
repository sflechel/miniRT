/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multifree_return_null.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:44:31 by sflechel          #+#    #+#             */
/*   Updated: 2025/02/14 17:44:32 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_1_return_null(void *arg1)
{
	free(arg1);
	return (0);
}

void	*free_2_return_null(void *arg1, void *arg2)
{
	free(arg1);
	free(arg2);
	return (0);
}

void	*free_3_return_null(void *arg1, void *arg2, void *arg3)
{
	free(arg1);
	free(arg2);
	free(arg3);
	return (0);
}

void	*free_4_return_null(void *arg1, void *arg2, void *arg3, void *arg4)
{
	free(arg1);
	free(arg2);
	free(arg3);
	free(arg4);
	return (0);
}
