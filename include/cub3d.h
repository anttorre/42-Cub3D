/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:37:03 by anttorre          #+#    #+#             */
/*   Updated: 2024/04/17 16:38:52 by anttorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "../libft/get_next_line_bonus.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# define WIDTH			1900
# define HEIGHT			1000
# define TILE_SIZE		30
# define FOV			60
# define ROTATION_SPEED	0.025
# define PLAYER_SPEED	2

/* ERROR CODES */
# define MTC	1	//Textures and colors not found
# define ME		2	//Map Empty
# define F		3	//File not found
# define EA		4	//Wrong extension or Arguments
# define DUP	5	//Duplicated Textures / Colors
# define IMG	6	//Can't load image
# define RGB	7	//Wrong RGB's

typedef struct s_player
{
	int		plyr_x;// player x position in pixels
	int		plyr_y;// player y position in pixels
	double	angle;// player angle
	float	fov_rd;// field of view in radians
	int		rot;// rotation flag
	int		l_r;// left right flag
	int		u_d;// up down flag
}	t_player;

typedef struct s_ray
{
	double	ray_ngl;// ray angle
	double	distance;// distance to the wall
	int		flag;// flag for the wall
}	t_ray;

typedef struct s_data //the data structure
{
	char			**map;// the map
	int				p_x;// player x position in the map
	int				p_y;// player y position in the map
	int				w_map;// map width
	int				h_map;// map height
	int				fd;
	char			*line;
	int				count_textures;
	int				i;
	int				j;
	int				k;
	char			**f_rgb;
	char			**c_rgb;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_image_t		*img; // the image
	mlx_t			*mlx;// the mlx pointer
	t_ray			*ray;// the ray structure
	t_player		*ply;// the player structure
}	t_data;

/* ERROR_MESSAGES.C */
int		error(int n);

/* PARSER.C */
int		check_extension(char *file);
int		parser(t_data *d, char *map_file);
int		save_map(t_data *d);

/* FREE.C */
void	free_b_arr(char ***s);
void	free_all(t_data *d);

#endif
