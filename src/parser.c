/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:29:43 by anttorre          #+#    #+#             */
/*   Updated: 2024/05/06 13:23:21 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_t_c(t_data *d, char **text)
{
	while (d->line && d->line[0] != '1' && d->line[0] != ' ')
	{
		if ((!ft_strncmp(d->line, "NO", 2) || !ft_strncmp(d->line, "SO", 2) \
		|| !ft_strncmp(d->line, "WE", 2) || !ft_strncmp(d->line, "EA", 2)) \
		&& (d->line[2] == ' ' || (d->line[2] >= 9 && d->line[2] <= 13)))
		{
			*text = ft_strjoin_gnl(*text, d->line);
			d->count_textures++;
		}
		else if ((!ft_strncmp(d->line, "F", 1) || !ft_strncmp(d->line, "C", 1)) \
			&& (d->line[1] == ' ' || (d->line[1] >= 9 && d->line[1] <= 13)))
		{
			*text = ft_strjoin_gnl(*text, d->line);
			d->count_textures++;
		}
		free(d->line);
		d->line = get_next_line(d->fd);
	}
	if (d->count_textures != 6)
		return (free(*text), free(d->line), error(MTC));
	if (save_map(d))
		return (free(*text), 1);
	return (close(d->fd), 0);
}

int	save_textures(t_data *d, char **split_text, char **tc)
{
	d->j = 2;
	while (split_text[d->i][d->j] == ' ' || \
	(split_text[d->i][d->j] >= 9 && split_text[d->i][d->j] <= 13))
		d->j++;
	*tc = ft_strdup(split_text[d->i] + d->j);
	if (!*tc)
		return (1);
	if (!ft_strncmp(split_text[d->i], "NO ", 3))
		d->no = mlx_load_png(*tc);
	else if (!ft_strncmp(split_text[d->i], "SO ", 3))
		d->so = mlx_load_png(*tc);
	else if (!ft_strncmp(split_text[d->i], "WE ", 3))
		d->we = mlx_load_png(*tc);
	else if (!ft_strncmp(split_text[d->i], "EA ", 3))
		d->ea = mlx_load_png(*tc);
	return (0);
}

int	check_colors(t_data *d, char *tc, char *split_text)
{
	int		j;
	int		comas;
	char	**rgb;

	d->k = -1;
	comas = 0;
	while (tc && tc[++d->k])
		if (tc[d->k] == ',')
			comas++;
	rgb = ft_split(tc, ',');
	d->k = -1;
	while (rgb && rgb[++d->k])
	{
		j = -1;
		while (rgb[d->k][++j])
			if (!ft_isdigit(rgb[d->k][j]))
				return (free_b_arr(&rgb), error(RGB));
		if (ft_atoi(rgb[d->k]) > 255 || ft_atoi(rgb[d->k]) < 0 || comas != 2)
			return (free_b_arr(&rgb), error(RGB));
	}
	if (!ft_strncmp(split_text, "F ", 2))
		d->f_rgb = rgb;
	else if (!ft_strncmp(split_text, "C ", 2))
		d->c_rgb = rgb;
	return (0);
}

int	save_t_c(t_data *d, char *text)
{
	char	**split_text;
	char	*tc;

	tc = NULL;
	split_text = ft_split(text, '\n');
	d->i = -1;
	while (split_text && split_text[++d->i])
	{
		d->j = d->i;
		while (split_text[++d->j])
			if (!ft_strncmp(split_text[d->i], split_text[d->j], 2))
				return (free_b_arr(&split_text), \
				free(text), free(d->line), error(DUP));
		if (split_text[d->i][d->j])
		{
			if (save_textures(d, split_text, &tc))
				return (free_b_arr(&split_text), free(tc), free(text), 1);
			if ((!ft_strncmp(split_text[d->i], "F ", 2) \
			|| !ft_strncmp(split_text[d->i], "C ", 2)) \
			&& check_colors(d, tc, split_text[d->i]))
				return (free_b_arr(&split_text), free(tc), free(text), 1);
			free(tc);
		}
	}
	return (free_b_arr(&split_text), free(text), 0);
}

int	parser(t_data *d, char *map_file)
{
	char	*text;

	text = NULL;
	d->count_textures = 0;
	d->fd = open(map_file, O_RDONLY);
	if (d->fd == -1)
		return (error(F));
	d->line = get_next_line(d->fd);
	if (!d->line)
		return (error(ME));
	if (check_t_c(d, &text))
		return (1);
	if (save_t_c(d, text))
		return (1);
	if (!d->no || !d->so || !d->we || !d->ea)
		return (free(d->line), error(IMG));
	if (!d->c_rgb || !d->c_rgb[0] || !d->c_rgb[1] || !d->c_rgb[2] \
	|| !d->f_rgb || !d->f_rgb[0] || !d->f_rgb[1] || !d->f_rgb[2])
		return (free(d->line), error(RGB));
	return (0);
}
