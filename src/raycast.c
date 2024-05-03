/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:58:37 by anttorre          #+#    #+#             */
/*   Updated: 2024/05/03 14:48:18 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

static float	horizontal(t_data *d, float angle)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angle);
	h_y = floor(d->player->y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &h_y, &y_step, 1);
	h_x = d->player->x + (h_y - d->player->y) / tan(angle);
	if ((unit_circle(angle, 'y') && x_step > 0) || \
		(!unit_circle(angle, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, d))
	{
		h_x += x_step;
		h_y += y_step;
	}
	d->ray->horiz_x = h_x;
	d->ray->horiz_y = h_y;
	return (sqrt(pow(h_x - d->player->x, 2) + pow(h_y - d->player->y, 2)));
}

static float	vertical(t_data *d, float angle)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angle);
	v_x = floor(d->player->x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angle, &v_x, &x_step, 0);
	v_y = d->player->y + (v_x - d->player->x) * tan(angle);
	if ((unit_circle(angle, 'x') && y_step < 0) || \
	(!unit_circle(angle, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, d))
	{
		v_x += x_step;
		v_y += y_step;
	}
	d->ray->vert_x = v_x;
	d->ray->vert_y = v_y;
	return (sqrt(pow(v_x - d->player->x, 2) + pow(v_y - d->player->y, 2)));
}

void	raycasting(t_data *d)
{
	double	horizontal_inter;
	double	vertical_inter;
	int		ray;

	ray = 0;
	d->ray->ray_angle = d->player->angle - (d->player->fov_rd / 2);
	while (ray < WIDTH)
	{
		d->ray->flag = 0;
		horizontal_inter = horizontal(d, correct_angle(d->ray->ray_angle));
		vertical_inter = vertical(d, correct_angle(d->ray->ray_angle));
		if (vertical_inter <= horizontal_inter)
			d->ray->distance = vertical_inter;
		else
		{
			d->ray->distance = horizontal_inter;
			d->ray->flag = 1;
		}
		rendering_game(d, ray);
		ray++;
		d->ray->ray_angle += (d->player->fov_rd / WIDTH);
	}
}
