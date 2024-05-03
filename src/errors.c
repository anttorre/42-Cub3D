/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:47:08 by anttorre          #+#    #+#             */
/*   Updated: 2024/05/03 13:18:39 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	error_2(int n)
{
	if (n == LIMITS)
		printf("Error\nHeight/Width/FOV out of limits\n");
	return (1);
}

int	error(int n)
{
	if (n == MTC)
		printf("Error\nTextures/Colors Incorrect\n");
	else if (n == ME)
		printf("Error\nEmpty map\n");
	else if (n == F)
		printf("Error\nFile not found\n");
	else if (n == EA)
		printf("Error\nWrong extension or Arguments\n");
	else if (n == DUP)
		printf("Error\nTextures/Colors duplicated\n");
	else if (n == IMG)
		printf("Error\nCan't load images\n");
	else if (n == RGB)
		printf("Error\nInvalid RGB\n");
	else if (n == MILF)
		printf("Error\nInvalid map format\n");
	else if (n == ELEM)
		printf("Error\nMap elements incorrect\n");
	else if (n == SP)
		printf("Error\nOnly spaces in first line\n");
	else if (n == WALLS)
		printf("Error\nMap not surrounded by walls\n");
	else if (n == HV)
		printf("Error\nMap H/V incorrect element\n");
	return (error_2(n));
}
