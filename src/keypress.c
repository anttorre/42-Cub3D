/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:19:14 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/26 16:03:35 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	keypress_2(mlx_key_data_t key, void *data)
{
	t_data	*d;

	d = data;
	if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
		d->ply->l_r = 0;
	else if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
		d->ply->l_r = 0;
	else if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
		d->ply->u_d = 0;
	else if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
		d->ply->u_d = 0;
	else if (key.key == MLX_KEY_LEFT && key.action == MLX_PRESS)
		d->ply->rot = 0;
	else if (key.key == MLX_KEY_RIGHT && key.action == MLX_PRESS)
		d->ply->rot = 0;
}

void	keypress(mlx_key_data_t key, void *data)
{
	t_data	*d;

	d = data;
	if (key.key == MLX_KEY_ESCAPE && (key.action == MLX_PRESS \
	|| key.action == MLX_REPEAT))
		close_game(data);
	else if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
		d->ply->l_r = -1;
	else if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
		d->ply->l_r = 1;
	else if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
		d->ply->u_d = -1;
	else if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
		d->ply->u_d = 1;
	else if (key.key == MLX_KEY_LEFT && key.action == MLX_PRESS)
		d->ply->rot = -1;
	else if (key.key == MLX_KEY_RIGHT && key.action == MLX_PRESS)
		d->ply->rot = 1;
}
