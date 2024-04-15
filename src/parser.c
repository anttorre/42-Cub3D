/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:29:43 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/15 18:10:08 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_extension(char *file)
{
	int	i;

	i = ft_strlen(file);
	if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c'
		|| file[i - 4] != '.')
		return (0);
	return (1);
}

/* int check_duplicates(t_data *d)
{
	
} */

int	read_textures_color(t_data *d, char *map_file)
{
	char	*text;
	char	**split_text;

	text = NULL;
	d->count_textures = 0;
	d->fd = open(map_file, O_RDONLY);
	if (d->fd == -1)
		return (printf("Error\nFile not found\n"), 1);
	d->line = get_next_line(d->fd);
	if (!d->line)
		return (printf("Error\nEmpty map\n"), 1);
	while (d->line && d->line[0] != '1' && d->line[0] != ' ')
	{
		if ((!ft_strncmp(d->line, "NO", 2) || !ft_strncmp(d->line, "SO", 2) \
		|| !ft_strncmp(d->line, "WE", 2) || !ft_strncmp(d->line, "EA", 2)) \
		&& (d->line[2] == ' ' || (d->line[2] >= 9 && d->line[2] <= 13)))
		{
			text = ft_strjoin_gnl(text, d->line);
			d->count_textures++;
		}
		else if ((!ft_strncmp(d->line, "F", 1) || !ft_strncmp(d->line, "C", 1)) \
			&& (d->line[1] == ' ' || (d->line[1] >= 9 && d->line[1] <= 13)))
		{
			text = ft_strjoin_gnl(text, d->line);
			d->count_textures++;
		}
		free(d->line);
		d->line = get_next_line(d->fd);
	}
	if (d->count_textures != 6)
		return (free(text), free(d->line), printf("Error\nT/C incorrect\n"), 1);
	split_text = ft_split(text, '\n');
	d->i = -1;
	while (split_text[++d->i])
	{
		d->j = d->i;
		while (split_text[++d->j])
			if (!ft_strncmp(split_text[d->i], split_text[d->j], 2))
				return (free_bidimensional_array(&split_text), free(text), free(d->line), printf("Error\nT/C duplicated\n"), 1);
	}
	return (free(text), free(d->line), 0);
}

int	parser(t_data *d, char *map_file)
{
	if (!read_textures_color(d, map_file))
		return (0);
	return (1);
}
