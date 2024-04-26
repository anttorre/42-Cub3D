/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:02:16 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/26 16:04:41 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_player_angle(t_data *d)
{
	char	player_orientation;

	player_orientation = d->map[d->p_y][d->p_x];
	if (player_orientation == 'N')
		d->ply->angle = 3 * M_PI / 2;
	if (player_orientation == 'S')
		d->ply->angle = M_PI / 2;
	if (player_orientation == 'E')
		d->ply->angle = 0;
	if (player_orientation == 'W')
		d->ply->angle = M_PI;
	d->ply->plyr_x = (d->p_x * TILE_SIZE) + TILE_SIZE / 2;
	d->ply->plyr_y = (d->p_y * TILE_SIZE) + TILE_SIZE / 2;
	d->ply->fov_rd = (FOV * M_PI / 180);
}

int	start_game(t_data *d)
{
	if (WIDTH > 2500 || HEIGHT > 1300 || FOV >= 180 || FOV <= 0)
		return (error(LIMITS));
	d->ply = ft_calloc(1, sizeof(t_player));
	d->ray = ft_calloc(1, sizeof(t_ray));
	d->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!d->ply || !d->ray || !d->mlx)
		return (1);
	get_player_angle(d);
	mlx_key_hook(d->mlx, &keypress, d);
	mlx_loop_hook(d->mlx, &draw_map, d);
	mlx_loop(d->mlx);
	return (0);
}
