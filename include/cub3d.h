/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:48:35 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/16 14:39:11 by fheld            ###   ########.fr       */
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
# include <limits.h>

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
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# define TINY_MAPX 100
# define TINY_MAPY 100

/**
 * TRA_Y denotes the transparency of the colors and ranges from 00 to FF
*/
# define TRA_Y 0x000000FF

// Color macros
# define L_BLUE 0x90EE90
# define L_RED 0xFF3B0190
# define L_WHITE 0xFFFFFFFF
# define YELLOW 0xFFEA00FF
# define GREY_A 0xC0C0C0FF
# define GREY_B 0xA0A0A0FF
# define GREY_C 0x707070FF
# define GREY_D 0x484848FF
# define SKY_BLUE 0x87CEEBAA
# define MUD_BROWN 0x553F23AA

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
 * dim_x and dim_y refer to the dimension of the acutal maze matrix
 *  (at the moment called maze_cpy)
*/
typedef struct s_dim
{
	int		lines;
	int		min_x;
	int		min_y;
	int		max_x;
	int		max_y;
	int		dim_x;
	int		dim_y;
}				t_dim;

typedef struct s_mlx42
{
	mlx_t		*mlx_ptr;
	xpm_t		*mm_black;
	xpm_t		*mm_white;
	xpm_t		*mm_grey;
	mlx_image_t	*mm_black_img;
	mlx_image_t	*mm_white_img;
	mlx_image_t	*mm_grey_img;
	mlx_image_t	*mm_player_img;
	mlx_image_t	*mm_floor_img;
	mlx_image_t	*mm_ceiling_img;
	mlx_image_t	*n_wall;
	mlx_image_t	*e_wall;
	mlx_image_t	*s_wall;
	mlx_image_t	*w_wall;
	mlx_image_t	*tiny_map;
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
	int			maze_number_of_lines;
	int			*maze_cpy_dim;
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

/**
 * holds two doubles repesenting x and y coorinates
*/
typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

// check_args.c
int			check_args(int ac, char **av);
int			check_file(char *path);

// math_helpers.c
double		dist(t_int_p2 a, t_int_p2 b);

// ray_collision.c
t_int_p2	horizontal_ray_collision(t_data *data, double angle);
t_int_p2	vertical_ray_collision(t_data *data, double angle);

// wall_collision.c
t_int_p2	hrc_up(t_data *data, double angle);
t_int_p2	hrc_down(t_data *data, double angle);
t_int_p2	vrc_left(t_data *data, double angle);
t_int_p2	vrc_right(t_data *data, double angle);

// draw_line_helper.c
void		truncate_coordinates2(t_data *data, t_int_p2 *a);
int			point_in_window(t_data *data, t_int_p2 *a);
void		truncate_coordinates(t_data *data, t_int_p2 *p);
int			abs1(int x);

// draw_line.c
void		draw_line_case_a(t_data *data, t_int_p2 a, t_int_p2 b, int color);
void		draw_line_case_b(t_data *data, t_int_p2 a, t_int_p2 b, int color);
void		draw_line(t_data *data, t_int_p2 a, t_int_p2 b, int color);

// draw_vertical.c
void		draw_vertical_line(t_data *data, int x, int height, int color);
void		draw_vertical_texture_n(t_data *data, int x, int d, t_int_p2 loc);
void		draw_vertical_texture_e(t_data *data, int x, int d, t_int_p2 loc);
void		draw_vertical_texture_s(t_data *data, int x, int d, t_int_p2 loc);
void		draw_vertical_texture_w(t_data *data, int x, int d, t_int_p2 loc);

// game.c
void		vertical_line(t_data *data, int x, double angle);
void		draw_game(void *arg);

// move_directions.c
void		move_up(t_data *data);
void		move_down(t_data *data);
void		move_left(t_data *data);
void		move_right(t_data *data);

// move_player.c
int			valid_pos(t_data *data, t_int_p2 pos);
void		move_forward(t_data *data);
void		move_backward(t_data *data);
void		move_player(void *arg);

// flood_fill_helper.c
void		print_all(char **maze, int lines);
char		**duplicate_maze(int lines, char **maze);
void		box_min_max(t_data *data, int x, int y);
void		create_dxy(int dxy[2][8]);
int			create_clean_maze(t_data *data);

// flood_fill.c
int			check_around(t_data *data, int dxy[2][8], int x, int y);
int			run_fill(t_data *data, int dxy[2][8], int x, int y);
void		mm_draw_floor(t_data *data, int y, int x);
void		mm_draw_objects(t_data *data, int y, int x);
int			flood_fill(t_data *data);

// ft_strjoin_mod.c
char		*ft_strjoin_mod(char *s1, char *s2);

// setup_detect.c
int			detect_colors(t_data *data, char *line, int *error);
int			detect_char(char c);
int			detect_textures(t_data *data, char *line, int *error);
int			check_for_start(t_data *data, char *buffer, int line);

// setup_file.c
char		*read_file(t_data *data, char *path);
int			parse_path(t_data *data, char *line, int len, int offset);
int			parse_colors(t_data *data, char *line, int len, int offset);
int			read_line(t_data *data, char *line);
int			setup_file(t_data *data, char **av);

// setup_helper.c
void		free_2d_array(char **array);
int			cont_str_len(char *line, int offset);
int			write_rgb(int *rgb, int red, int green, int blue);
void		replace_nl(char **buffer);
int			init_data(t_data *data);

// render_create.c
int			create_wall_images(t_data *data);
int			create_tiny_map(t_data *data);
int			create_floor_ceiling_image(t_data *data);
int			create_image_player(t_data *data);

// render_draw.c
void		draw_picture(mlx_t *mlx_ptr, mlx_image_t *picture, int y, int x);
void		check_for_tile(t_data *data, void (*f)(t_data *data, int, int));
void		draw_floor(t_data *data, int y, int x);
void		which_picture(t_data *data, int y, int x);
void		draw_player(void *arg);

// render_hooks.c
void		esc_hook(void *arg);
void		add_hooks(t_data *data);

// render_load_fill.c
void		load_texture(mlx_t *mlx, mlx_image_t **image, char *path);
void		load_pics(t_data *data);
void		fill_ceiling(t_data *data);
void		fill_floor(t_data *data);
void		set_dim(t_data *data);

// render_map.c
void		ray(t_data *data, double angle);
void		clear_image(t_data *data);
int			start_mlx(t_data *data);
int			render_map(t_data *data);
void		delete_four_textures(mlx_texture_t *north, mlx_texture_t *east, \
				mlx_texture_t *south, mlx_texture_t *west);

// new protection functions in flood_fill.c
int	valid_index(t_data *data, int x, int y);
int	set_maze_cpy_dim(t_data *data);

#endif
