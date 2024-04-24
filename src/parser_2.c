/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:09:56 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/24 13:08:40 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	save_map(t_data *d)
{
	char	*map_join;

	map_join = NULL;
	while (d->line)
	{
		map_join = ft_strjoin_gnl(map_join, d->line);
		if (!map_join)
			return (1);
		if (d->line[0] == '\n')
			return (free(map_join), free(d->line), error(MILF));
		free(d->line);
		d->line = get_next_line(d->fd);
	}
	close(d->fd);
	if (map_join)
	{
		d->map = ft_split(map_join, '\n');
		if (!d->map)
			return (free(map_join), 1);
		if (check_map(d))
			return (free(map_join), 1);
	}
	return (free(map_join), 0);
}
