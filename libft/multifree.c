/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multifree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 08:53:49 by sflechel          #+#    #+#             */
/*   Updated: 2025/02/12 08:53:55 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	free_1(void *arg1)
{
	free(arg1);
}

void	free_2(void *arg1, void *arg2)
{
	free(arg1);
	free(arg2);
}

void	free_3(void *arg1, void *arg2, void *arg3)
{
	free(arg1);
	free(arg2);
	free(arg3);
}

void	free_4(void *arg1, void *arg2, void *arg3, void *arg4)
{
	free(arg1);
	free(arg2);
	free(arg3);
	free(arg4);
}
