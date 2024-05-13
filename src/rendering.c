/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:15:51 by anttorre          #+#    #+#             */
/*   Updated: 2024/05/13 14:35:59 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_floor_ceiling(t_data *d, int ray, int t_pix, int b_pix)
{
	int		i;
	int		c;

	i = b_pix;
	c = get_rgba(ft_atoi(d->f_rgb[0]), ft_atoi(d->f_rgb[1]), \
		ft_atoi(d->f_rgb[2]), 255);
	while (i < HEIGHT)
		put_pixel(d, ray, i++, c);
	c = get_rgba(ft_atoi(d->c_rgb[0]), ft_atoi(d->c_rgb[1]), \
		ft_atoi(d->c_rgb[2]), 255);
	i = 0;
	while (i < t_pix)
		put_pixel(d, ray, i++, c);
}

static mlx_texture_t	*get_texture(t_data *d, int flag)
{
	d->ray->ray_angle = correct_angle(d->ray->ray_angle);
	if (flag == 0)
	{
		if (d->ray->ray_angle > M_PI / 2 \
		&& d->ray->ray_angle < 3 * (M_PI / 2))
			return (d->ea);
		else
			return (d->we);
	}
	else
	{
		if (d->ray->ray_angle > 0 && d->ray->ray_angle < M_PI)
			return (d->so);
		else
			return (d->no);
	}
}

static double	get_x_ray_origin(mlx_texture_t	*texture, t_data *d)
{
	double	x_o;

	if (d->ray->flag == 1)
		x_o = (int)fmodf((d->ray->horiz_x * \
		(texture->width / TILE_SIZE)), texture->width);
	else
		x_o = (int)fmodf((d->ray->vert_y * \
		(texture->width / TILE_SIZE)), texture->width);
	return (x_o);
}

static void	draw_wall(t_data *d, int t_pix, int b_pix, double wall_h)
{
	double			x_ray_o;
	double			y_ray_o;
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			factor;

	texture = get_texture(d, d->ray->flag);
	arr = (uint32_t *)texture->pixels;
	factor = (double)texture->height / wall_h;
	x_ray_o = get_x_ray_origin(texture, d);
	y_ray_o = (t_pix - (HEIGHT / 2) + (wall_h / 2)) * factor;
	if (y_ray_o < 0)
		y_ray_o = 0;
	while (t_pix < b_pix)
	{
		put_pixel(d, d->ray->index, t_pix, reverse_bytes \
		(arr[(int)y_ray_o * texture->width + (int)x_ray_o]));
		y_ray_o += factor;
		t_pix++;
	}
}

void	rendering_game(t_data *d, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	d->ray->distance *= cos(correct_angle(d->ray->ray_angle \
	- d->player->angle));
	wall_h = (TILE_SIZE / d->ray->distance) * ((WIDTH / 2) \
	/ tan(d->player->fov_rd / 2));
	b_pix = (HEIGHT / 2) + (wall_h / 2);
	t_pix = (HEIGHT / 2) - (wall_h / 2);
	if (b_pix > HEIGHT)
		b_pix = HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	d->ray->index = ray;
	draw_wall(d, t_pix, b_pix, wall_h);
	draw_floor_ceiling(d, ray, t_pix, b_pix);
}
