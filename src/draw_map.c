/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:07:14 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/26 16:07:01 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_map(void *data)
{
	t_data	*d;

	d = data;
	mlx_delete_image(d->mlx, d->img);
	d->img = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(d->mlx, d->img, 0, 0);
}
