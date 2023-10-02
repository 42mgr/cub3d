/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:48:35 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/02 16:46:45 by fheld            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft-42/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <math.h>

# define NORTH 0
# define EAST 90
# define SOUTH 180
# define WEST 270
# define DEFAULT_NORTH_TEXTURE "./textures/default_n_wall"
# define DEFAULT_SOUTH_TEXTURE "./textures/default_s_wall"
# define DEFAULT_WEST_TEXTURE "./textures/default_w_wall"
# define DEFAULT_EAST_TEXTURE "./textures/default_e_wall"
# define SPRITE_SIZE 64
# define WALL_OFFSET 5
# define L_BLUE 0x6DC5FF
# define L_GREEN 0x90EE90
# define L_RED 0xFFCCCB

/**
 * Player is intialized at starting position with view direction (N, S, E or W)
 * TBD: in degrees or radians ???
 * later these values update to the current position and view direction
*/
typedef struct s_player
{
	int	x;
	int	y;
	int	dir;
}				t_player;

/**
 * Valid paths to textures and valid colors are saved here
*/
typedef struct s_textures
{
	char	*n_path;
	char	*s_path;
	char	*w_path;
	char	*e_path;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
}					t_textures;

/**
 * The linked list to save the length of each line (while parsing)
 * useful to check if the request for an arry position is within valid boundaries
*/
typedef struct s_llen
{
	int				lno;
	int				llen;
	struct s_llen	*next;
}				t_llen;

/**
 * Helps to navigate around the char **maze, stay inside boundaries
 * and draw the 2D minimap
*/
typedef struct s_dim
{
	int		lines;
	int		min_x;
	int		min_y;
	int		max_x;
	int		max_y;
}				t_dim;

typedef struct s_mlx42
{
	mlx_t	*mlx_ptr;
	xpm_t	*mm_black;
	xpm_t	*mm_white;
	xpm_t	*mm_grey;
	mlx_image_t *mm_black_img;
	mlx_image_t *mm_white_img;
	mlx_image_t *mm_grey_img;
	mlx_image_t	*mm_player_img;
}			t_mlx42;

/**
 * The struct that contains them all and is passed around
*/
typedef struct s_data
{
	mlx_t		*mlx;
	t_player	start;
	t_textures	textures;
	char		**maze;
	char		**maze_cpy;
	t_dim		dim;
	t_mlx42		mlx42;
}				t_data;

/**
 * The struct contains two ints that mean the x/y position on a plane
*/
typedef struct s_int_p2
{
	int	x;
	int	y;
}				t_int_p2;

// check_args.c
int		check_args(int ac, char **av);
int		check_file(char *path);

// setup_file.c
int		setup_file(t_data *data, char **av);

// flood_fill.c
int		flood_fill(t_data *data);

char	*ft_strjoin_mod(char *s1, char *s2);
int		render_map(t_data *data);
void	free_2d_array(char **array);
void	check_for_tile(t_data *data, void (*f)(t_data *data, int, int));
void	draw_picture(mlx_t *mlx_ptr, mlx_image_t *picture, int y, int x);

// draw map
void	create_image_player(t_data *data);

// draw line
void 	draw_line(t_data *data, t_int_p2 a, t_int_p2 b, int color);

// move_player.c
void	move_up(t_data *data);
void	move_down(t_data *data);
void	move_left(t_data *data);
void	move_right(t_data *data);
void 	move_player(void* arg);

#endif
