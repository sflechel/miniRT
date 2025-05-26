/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multifree_return_zero.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:44:38 by sflechel          #+#    #+#             */
/*   Updated: 2025/02/14 17:44:39 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_1_return_0(void *arg1)
{
	free(arg1);
	return (0);
}

int	free_2_return_0(void *arg1, void *arg2)
{
	free(arg1);
	free(arg2);
	return (0);
}

int	free_3_return_0(void *arg1, void *arg2, void *arg3)
{
	free(arg1);
	free(arg2);
	free(arg3);
	return (0);
}

int	free_4_return_0(void *arg1, void *arg2, void *arg3, void *arg4)
{
	free(arg1);
	free(arg2);
	free(arg3);
	free(arg4);
	return (0);
}
