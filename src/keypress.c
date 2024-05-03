/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:19:14 by anttorre          #+#    #+#             */
/*   Updated: 2024/05/03 13:55:26 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	player_rotation(t_data *d, int i)
{
	if (i == 1)
	{
		d->player->angle += ROTATION_SPEED;
		if (d->player->angle > 2 * M_PI)
			d->player->angle -= 2 * M_PI;
	}
	else
	{
		d->player->angle -= ROTATION_SPEED;
		if (d->player->angle < 0)
			d->player->angle += 2 * M_PI;
	}
}

static void	player_move(t_data *d, double move_x, double move_y)
{
	int		map_y;
	int		map_x;
	int		new_x;
	int		new_y;

	new_x = roundf(d->player->x + move_x);
	new_y = roundf(d->player->y + move_y);
	map_x = (new_x / TILE_SIZE);
	map_y = (new_y / TILE_SIZE);
	if (d->map[map_y][map_x] != '1' \
	&& (d->map[map_y][d->player->x / TILE_SIZE] != '1' \
	&& d->map[d->player->y / TILE_SIZE][map_x] != '1'))
	{
		d->player->x = new_x;
		d->player->y = new_y;
	}
}

void	rot_l_r_player(t_data *d, double move_x, double move_y)
{
	if (d->player->rot == 1)
		player_rotation(d, 1);
	if (d->player->rot == -1)
		player_rotation(d, 0);
	if (d->player->l_r == 1)
	{
		move_x = -sin(d->player->angle) * PLAYER_SPEED;
		move_y = cos(d->player->angle) * PLAYER_SPEED;
	}
	if (d->player->l_r == -1)
	{
		move_x = sin(d->player->angle) * PLAYER_SPEED;
		move_y = -cos(d->player->angle) * PLAYER_SPEED;
	}
	if (d->player->u_d == 1)
	{
		move_x = cos(d->player->angle) * PLAYER_SPEED;
		move_y = sin(d->player->angle) * PLAYER_SPEED;
	}
	if (d->player->u_d == -1)
	{
		move_x = -cos(d->player->angle) * PLAYER_SPEED;
		move_y = -sin(d->player->angle) * PLAYER_SPEED;
	}
	player_move(d, move_x, move_y);
}

static void	keypress_2(mlx_key_data_t key, void *data)
{
	t_data	*d;

	d = data;
	if (key.key == MLX_KEY_A && key.action == MLX_RELEASE)
		d->player->l_r = 0;
	else if (key.key == MLX_KEY_D && key.action == MLX_RELEASE)
		d->player->l_r = 0;
	else if (key.key == MLX_KEY_W && key.action == MLX_RELEASE)
		d->player->u_d = 0;
	else if (key.key == MLX_KEY_S && key.action == MLX_RELEASE)
		d->player->u_d = 0;
	else if (key.key == MLX_KEY_LEFT && key.action == MLX_RELEASE)
		d->player->rot = 0;
	else if (key.key == MLX_KEY_RIGHT && key.action == MLX_RELEASE)
		d->player->rot = 0;
}

void	keypress(mlx_key_data_t key, void *data)
{
	t_data	*d;

	d = data;
	if (key.key == MLX_KEY_ESCAPE && (key.action == MLX_PRESS \
	|| key.action == MLX_REPEAT))
		close_game(data);
	else if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
		d->player->l_r = -1;
	else if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
		d->player->l_r = 1;
	else if (key.key == MLX_KEY_W && key.action == MLX_PRESS)
		d->player->u_d = 1;
	else if (key.key == MLX_KEY_S && key.action == MLX_PRESS)
		d->player->u_d = -1;
	else if (key.key == MLX_KEY_LEFT && key.action == MLX_PRESS)
		d->player->rot = -1;
	else if (key.key == MLX_KEY_RIGHT && key.action == MLX_PRESS)
		d->player->rot = 1;
	keypress_2(key, data);
}
