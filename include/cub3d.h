/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anttorre <atormora@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:37:03 by anttorre          #+#    #+#             */
/*   Updated: 2024/05/02 16:24:42 by anttorre         ###   ########.fr       */
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
# define WIDTH			2500
# define HEIGHT			1300
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
# define MILF	8	// Mapé incorrecté le formaté
# define ELEM	9	//Elementos del mapa incorrectos
# define SP		10	//Espacios en la linea 1
# define WALLS	11	//Faltan paredes o no esta cerrado por paredes
# define HV		12	//Map H/V incorrect element
# define LIMITS	13	// Height Width FOV out of limits

typedef struct s_player
{
	int		x;// player x position in pixels
	int		y;// player y position in pixels
	double	angle;// player angle
	float	fov_rd;// field of view in radians
	int		rot;// rotation flag
	int		l_r;// left right flag
	int		u_d;// up down flag
}	t_player;

typedef struct s_ray
{
	int		index;
	double	ray_angle;// ray angle
	double	distance;// distance to the wall
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
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
	int				c_pos; //Contador de los elementos del mapa
	char			orientation; // Caracter de la orientacion del personaje
	char			*line;
	int				count_textures;
	int				i;
	int				j;
	int				k;
	char			c;
	char			**f_rgb;
	char			**c_rgb;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_image_t		*img; // the image
	mlx_t			*mlx;// the mlx pointer
	t_ray			*ray;// the ray structure
	t_player		*player;// the player structure
}	t_data;

/* ERROR_MESSAGES.C */
int		error(int n);

/* PARSER.C */
int		check_extension(char *file);
int		parser(t_data *d, char *map_file);
int		save_map(t_data *d);

/* CHECK_MAP.C */
int		check_map(t_data *d);

/* FREE.C */
void	free_b_arr(char ***s);
void	free_all(t_data *d);

int		start_game(t_data *d);

void	start_map(void *data);

void	keypress(mlx_key_data_t key, void *data);

void	rot_l_r_player(t_data *d, double move_x, double move_y);

int		wall_hit(float x, float y, t_data *d);

float	correct_angle(float angle);

int		unit_circle(float angle, char c);

void	raycasting(t_data *d);

void	close_game(void *data);

#endif
