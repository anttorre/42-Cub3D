/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:06:12 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/24 17:21:21 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_only_spaces_fl(t_data *d)
{
	d->i = -1;
	while (d->map && d->map[++d->i])
	{
		while (d->i == 0 && (d->map[d->i][d->j] == 32 \
		|| (d->map[d->i][d->j] >= 9 && d->map[d->i][d->j] <= 13)))
			d->j++;
		if (d->i == 0 && (d->map[d->i][d->j] != '1' \
		|| d->map[d->i][ft_strlen(d->map[d->i]) - 1] != '1'))
			return (error(SP));
	}
	return (0);
}

int	check_elements_map(t_data *d)
{
	char	c;

	d->i = -1;
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
	return (0);
}

int	fix_map(t_data *d)
{
	size_t	max_l;
	char	*new_ln;

	d->i = -1;
	max_l = 0;
	while (d->map[++d->i])
		if (max_l < ft_strlen(d->map[d->i]))
			max_l = ft_strlen(d->map[d->i]);
	d->i = -1;
	while (d->map[++d->i])
	{
		d->j = ft_strlen(d->map[d->i]);
		new_ln = ft_calloc(1, max_l + 1);
		if (!new_ln)
			return (1);
		ft_strlcpy(new_ln, d->map[d->i], ft_strlen(d->map[d->i]) + 1);
		while ((size_t)d->j < max_l)
			new_ln[d->j++] = ' ';
		new_ln[d->j] = '\0';
		free(d->map[d->i]);
		d->map[d->i] = new_ln;
		d->h_map = d->i;
		d->w_map = max_l - 1;
	}
	return (0);
}

int	check_map(t_data *d)
{
	char	c;

	if (check_only_spaces_fl(d) || check_elements_map(d) || fix_map(d))
		return (1);
	d->i = -1;
	while (d->map[++d->i])
	{
		d->j = -1;
		while (d->map[d->i][++d->j])
		{
			c = d->map[d->i][d->j];
			if ((d->i == 0 || d->i == d->h_map) \
			&& d->map[d->i][d->j] != ' ' && d->map[d->i][d->j] != '1')
				return (error(WALLS));
			if ((d->j == 0 || d->j == d->w_map) \
			&& d->map[d->i][d->j] != ' ' && d->map[d->i][d->j] != '1')
				return (error(WALLS));
			if (d->i != 0 && d->i != d->h_map && (c == '0' \
			|| c == 'N' || c == 'S' || c == 'E' || c == 'W') \
			&& ((d->map[d->i][d->j - 1] == 32 || d->map[d->i][d->j + 1] == 32) \
			|| (d->map[d->i - 1][d->j] == 32 || d->map[d->i + 1][d->j] == 32)))
				return (error(HV));
		}
	}
	return (0);
}
