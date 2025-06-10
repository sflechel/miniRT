/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflechel <sflechel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:00:23 by sflechel          #+#    #+#             */
/*   Updated: 2025/06/10 10:00:36 by sflechel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

t_vec3	ortho_proj(const t_vec3 projected, const t_vec3 line)
{
	return (scalar_mult(line, dot_product(line, projected)));
}
