/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:35:02 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/15 17:31:20 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2 || !check_extension(argv[1]))
		return (printf("Error\nInvalid Arguments.\n"), 1);
	if (parser(&data, argv[1]))
		return (1);
	return (0);
}
