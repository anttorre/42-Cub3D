/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:06:12 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/24 13:00:36 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_map(t_data *d)
{
	char	*new_ln;
	size_t	max_l;
	char	c;

	d->i = -1;
	max_l = 0;
	while (d->map && d->map[++d->i])
	{
		d->j = -1;
		while (d->map[d->i][++d->j])
		{
			c = d->map[d->i][d->j];
			if (c != 32 && c != '1' && c != '0' \
			&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
				return (error(ELEM));
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				d->c_pos++;
				d->orientation = c;
			}
		}
	}
	if (d->c_pos != 1)
		return (error(ELEM));
	d->i = -1;
	while (d->map[++d->i])
		if (max_l < ft_strlen(d->map[d->i]))
			max_l = ft_strlen(d->map[d->i]);
	d->i = -1;
	while (d->map[++d->i])
	{
		d->j = ft_strlen(d->map[d->i]);
		new_ln = ft_calloc(1, max_l + 1);
		ft_strlcpy(new_ln, d->map[d->i], ft_strlen(d->map[d->i]) + 1);
		while ((size_t)d->j < max_l)
			new_ln[d->j++] = ' ';
		free(d->map[d->i]);
		d->map[d->i] = new_ln;
		d->h_map = d->i;
		d->w_map = max_l - 1;
	}
	d->i = -1;
	while (d->map[++d->i])
	{
		d->j = -1;
		while (d->map[d->i][++d->j])
		{
			if ((d->i == 0 || d->i == d->h_map) \
			&& d->map[d->i][d->j] != ' ' && d->map[d->i][d->j] != '1')
				return (printf("Error paredes\n"), 1);
			if ((d->j == 0 || d->j == d->w_map) \
			&& d->map[d->i][d->j] != ' ' && d->map[d->i][d->j] != '1')
				return (printf("Error paredes laterales\n"), 1);
			c = d->map[d->i][d->j];
			if (d->i != 0 && d->i != d->h_map && (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W') && ((d->map[d->i][d->j - 1] == ' ' || d->map[d->i][d->j + 1] == ' ') || (d->map[d->i - 1][d->j] == ' ' || d->map[d->i + 1][d->j] == ' ')))
				return (printf("Error te comiste un pingo\n"), 1);
		}
	}
	int i = -1;
	while (d->map[++i])
		printf("%s\n", d->map[i]);
	return (0);
}
