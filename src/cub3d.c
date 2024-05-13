/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:35:02 by anttorre          #+#    #+#             */
/*   Updated: 2024/05/06 13:26:28 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* IMPRIMIR MAPA
	int i = -1;
	while (d->map[++i])
		printf("%s\n", d->map[i]);
*/

/* FUNCION PARA LEAKS */
void	ft_leaks(void)
{
	system("leaks -q cub3D");
}


static void	init_data(t_data *d)
{
	d->c_rgb = NULL;
	d->f_rgb = NULL;
	d->count_textures = 0;
	d->fd = 0;
	d->i = 0;
	d->j = 0;
	d->k = 0;
	d->h_map = 0;
	d->w_map = 0;
	d->ea = NULL;
	d->no = NULL;
	d->so = NULL;
	d->we = NULL;
	d->img = NULL;
	d->line = NULL;
	d->map = NULL;
	d->mlx = NULL;
	d->p_x = 0;
	d->p_y = 0;
	d->player = NULL;
	d->ray = NULL;
	d->c_pos = 0;
}

static int	check_extension(char *file)
{
	int	i;

	i = ft_strlen(file);
	if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c'
		|| file[i - 4] != '.')
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	atexit(ft_leaks);
	if (argc != 2 || !check_extension(argv[1]))
		return (error(EA));
	init_data(&data);
	if (parser(&data, argv[1]))
		return (free_all(&data), 1);
	if (start_game(&data))
		return (free_all(&data), 1);
	return (free_all(&data), 0);
}
