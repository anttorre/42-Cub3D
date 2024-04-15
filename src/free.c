/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 18:03:53 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/15 18:04:09 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_bidimensional_array(char ***s)
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