/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:02:16 by anttorre          #+#    #+#             */
/*   Updated: 2024/05/03 13:49:53 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	wall_hit(float x, float y, t_data *d)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if ((y_m >= d->h_map || x_m >= d->w_map))
		return (0);
	if (d->map[y_m] && x_m <= (int)ft_strlen(d->map[y_m]))
		if (d->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	correct_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

static void	get_player_angle(t_data *d)
{
	char	player_orientation;

	player_orientation = d->map[d->p_y][d->p_x];
	if (player_orientation == 'N')
		d->player->angle = 3 * M_PI / 2;
	if (player_orientation == 'S')
		d->player->angle = M_PI / 2;
	if (player_orientation == 'E')
		d->player->angle = 0;
	if (player_orientation == 'W')
		d->player->angle = M_PI;
	d->player->x = (d->p_x * TILE_SIZE) + TILE_SIZE / 2;
	d->player->y = (d->p_y * TILE_SIZE) + TILE_SIZE / 2;
	d->player->fov_rd = (FOV * M_PI / 180);
}

int	start_game(t_data *d)
{
	if (WIDTH > 2500 || HEIGHT > 1300 || FOV >= 180 || FOV <= 0)
		return (error(LIMITS));
	d->player = ft_calloc(1, sizeof(t_player));
	d->ray = ft_calloc(1, sizeof(t_ray));
	d->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!d->player || !d->ray || !d->mlx)
		return (1);
	get_player_angle(d);
	mlx_key_hook(d->mlx, &keypress, d);
	mlx_loop_hook(d->mlx, &start_map, d);
	mlx_loop(d->mlx);
	return (0);
}
