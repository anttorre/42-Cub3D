/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:03:53 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/25 15:56:16 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_b_arr(char ***s)
{
	int	a;

	if (*s != NULL)
	{
		a = -1;
		while ((*s)[++a] != NULL)
		{
			free((*s)[a]);
			(*s)[a] = NULL;
		}
		free(*s);
		*s = NULL;
	}
}

void	free_all_2(t_data *d)
{
	int	i;

	if (d->c_rgb)
	{
		i = -1;
		while (d->c_rgb[++i])
		{
			free(d->c_rgb[i]);
			d->c_rgb[i] = NULL;
		}
		free(d->c_rgb);
		d->c_rgb = NULL;
	}
	if (d->no)
		mlx_delete_texture(d->no);
	if (d->so)
		mlx_delete_texture(d->so);
	if (d->we)
		mlx_delete_texture(d->we);
	if (d->ea)
		mlx_delete_texture(d->ea);
	if (d->ply)
		free(d->ply);
	if (d->ray)
		free(d->ray);
}

void	free_all(t_data *d)
{
	int	i;

	i = -1;
	if (d->map)
	{
		while (d->map[++i])
		{
			free(d->map[i]);
			d->map[i] = NULL;
		}
		free(d->map);
		d->map = NULL;
	}
	if (d->f_rgb)
	{
		i = -1;
		while (d->f_rgb[++i])
		{
			free(d->f_rgb[i]);
			d->f_rgb[i] = NULL;
		}
		free(d->f_rgb);
		d->f_rgb = NULL;
	}
	free_all_2(d);
}
