/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:02:16 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/25 15:55:16 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	start_game(t_data *d)
{
	if (WIDTH > 2500 || HEIGHT > 1300 || FOV >= 180 || FOV <= 0)
		return (error(LIMITS));
	d->ply = ft_calloc(1, sizeof(t_player));
	d->ray = ft_calloc(1, sizeof(t_ray));
	d->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!d->ply || !d->ray || !d->mlx)
		return (1);
	mlx_loop(d->mlx);
	return (0);
}
