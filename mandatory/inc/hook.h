/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edarnand <edarnand@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:40:39 by edarnand          #+#    #+#             */
/*   Updated: 2025/05/22 18:05:41 by edarnand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

# define KEY_ESCAPE 65307
# define KEY_LSHIFT 65505
# define KEY_SPACE ' '
# define KEY_ARROW_LEFT 65361
# define KEY_ARROW_RIGHT 65363
# define KEY_ARROW_UP 65362
# define KEY_ARROW_DOWN 65364
# define KEY_MINUS '-'
# define KEY_EQUAL '='
# define KEY_W 'w'
# define KEY_A 'a'
# define KEY_S 's'
# define KEY_D 'd'

# include "minirt.h"

typedef struct s_hook_data
{
	t_mlx		*mlx;
	t_camera	*cam;
}	t_hook_data;

int		key_hook(int keycode, void *data_v);
void	handle_hooks(t_hook_data *data);

#endif
