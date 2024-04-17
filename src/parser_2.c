/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:09:56 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/17 16:32:44 by anttorre         ###   ########.fr       */
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
		free(d->line);
		d->line = get_next_line(d->fd);
	}
	d->map = ft_split(map_join, '\n');
	if (!d->map)
		return (free(map_join), 1);
	return (free(map_join), 0);
}
