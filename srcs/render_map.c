/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:10:50 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/12 14:56:18 by fheld            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_texture(mlx_t *mlx, mlx_image_t **image, char *path)
{
	xpm_t	*texture;

	texture = mlx_load_xpm42(path);
	*image = mlx_texture_to_image(mlx, &texture->texture);
	mlx_delete_texture(&texture->texture);
}

void	load_pics(t_data *data)
{
	load_texture(data->mlx42.mlx_ptr, &(data->mlx42.mm_black_img), "textures/minimap/mm_black_64x64.xpm42");
	load_texture(data->mlx42.mlx_ptr, &(data->mlx42.mm_grey_img), "textures/minimap/mm_grey_64x64.xpm42");
	load_texture(data->mlx42.mlx_ptr, &(data->mlx42.mm_white_img), "textures/minimap/mm_white_64x64.xpm42");
}

void	draw_picture(mlx_t *mlx_ptr, mlx_image_t *picture, int y, int x)
{
	mlx_image_to_window(mlx_ptr, picture, x, y);
}

void	check_for_tile(t_data *data, void (*f)(t_data *data, int, int))
{
	int	x;
	int	y;

	y = 0;
	while (data->maze[y + data->dim.min_y] && y < data->dim.max_y - data->dim.min_y + 1)
	{
		x = 0;
		while (x < data->dim.max_x - data->dim.min_x + 1)
		{
			f(data, y, x);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_data *data, int y, int x)
{
	draw_picture(data->mlx42.mlx_ptr, data->mlx42.mm_black_img, \
		(y * SPRITE_SIZE), (x * SPRITE_SIZE));
}

void	which_picture(t_data *data, int y, int x)
{
	if (data->maze[y + data->dim.min_y][x + data->dim.min_x] == '1')
	{
		draw_picture(data->mlx42.mlx_ptr, data->mlx42.mm_grey_img, \
			(y * SPRITE_SIZE), (x * SPRITE_SIZE));
	}
	else if (data->maze[y + data->dim.min_y][x + data->dim.min_x] == '0')
	{
		draw_picture(data->mlx42.mlx_ptr, data->mlx42.mm_white_img, \
			(y * SPRITE_SIZE), (x * SPRITE_SIZE));
	}
}

void esc_hook(void* arg)
{
	mlx_t* mlx;

	mlx = arg;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

/**
 * creates new image
 * sets inital position of player
 * puts image to window
*/
void	create_image_player(t_data *data)
{
	data->start.x = (data->start.x - data->dim.min_x) * SPRITE_SIZE + (SPRITE_SIZE / 2);
	data->start.y = (data->start.y - data->dim.min_y) * SPRITE_SIZE + (SPRITE_SIZE / 2);
	data->mlx42.mm_player_img = mlx_new_image(data->mlx42.mlx_ptr, \
		(data->dim.max_x - data->dim.min_x + 1) * SPRITE_SIZE, \
		(data->dim.max_y - data->dim.min_y + 1) * SPRITE_SIZE);
	mlx_image_to_window(data->mlx42.mlx_ptr, data->mlx42.mm_player_img, 0, 0);
}

void	ray(t_data *data, double angle)
{
	t_int_p2	q;
	t_int_p2	p;
	double		dist_to_q;
	double		dist_to_p;
	
	q = horizontal_ray_collision(data, angle);
	p = vertical_ray_collision(data, angle);
	dist_to_p = dist((t_int_p2){data->start.x, data->start.y}, p);
	dist_to_q = dist((t_int_p2){data->start.x, data->start.y}, q);
	if (dist_to_p >= dist_to_q || isnan(dist_to_p) == 1)
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, q, L_BLUE);	
	else if (dist_to_p < dist_to_q || isnan(dist_to_q) == 1)
	{
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, p, L_RED);
	}
	else if (p.x == 0 && p.y == 0)
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, p, YELLOW);
	else if (q.x == 0 && q.y == 0)
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, p, YELLOW);
	else
		draw_line(data, (t_int_p2){100, 100}, (t_int_p2){400, 400}, YELLOW);
}

void	clear_image(t_data *data)
{
	ft_memset(data->mlx42.mm_player_img->pixels, 0x00, sizeof(uint8_t) * \
		data->dim.dim_x * SPRITE_SIZE * data->dim.dim_y * SPRITE_SIZE * 4);
}

// the last multipier by 4 is needed because 
//every pixel consists of 4 consecutive uint_8 s
void draw_player(void* arg)
{
	t_data		*data;
	// int			ray_angle;
	
	data = arg;
	// int i = 0;
	// ray_angle = ((data->start.dir + 23) % 360) * 10;
	clear_image(data);
	// while (i < 460)
	// {
	// 	ray(data, ray_angle * M_PI / 1800.0);
	// 	ray_angle = (ray_angle + 3599) % 3600;
	// 	i++;
	// }
	return ;
}

void	fill_ceiling(t_data *data)
{
	int i;
	int	j;
	int	height;
	int	width;
	int color;

	i = 0;
	j = 0;
	height = WINDOW_HEIGHT / 2;
	width = WINDOW_WIDTH;
	color = TRA_Y + data->textures.ceiling_rgb[2] * 0x100 + \
			data->textures.ceiling_rgb[1] * 0x10000 + \
			data->textures.ceiling_rgb[0] * 0x1000000;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			mlx_put_pixel(data->mlx42.mm_ceiling_img, i, j, color);
			i++;
		}
		j++;
	}
}

void	fill_floor(t_data *data)
{
	int i;
	int	j;
	int	height;
	int	width;
	int color;

	height = WINDOW_HEIGHT / 2;
	width = WINDOW_HEIGHT;
	i = 0;
	j = 0;
	color = TRA_Y + data->textures.floor_rgb[2] * 0x100 + \
		data->textures.floor_rgb[1] * 0x10000 + \
		data->textures.floor_rgb[0] * 0x1000000;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			mlx_put_pixel(data->mlx42.mm_floor_img, i, j, color);
			i++;
		}
		j++;
	}
}

void	create_floor_ceiling_image(t_data *data)
{
	mlx_t	*mlx;
	int		height;
	int		width;

	mlx = data->mlx42.mlx_ptr;
	height = WINDOW_HEIGHT / 2;
	width = WINDOW_WIDTH;
	data->mlx42.mm_floor_img = mlx_new_image(data->mlx42.mlx_ptr, width, height);
	data->mlx42.mm_ceiling_img = mlx_new_image(data->mlx42.mlx_ptr, width, height);
	fill_ceiling(data);
	fill_floor(data);
	mlx_image_to_window(mlx, data->mlx42.mm_ceiling_img, 0, 0);
	mlx_image_to_window(mlx, data->mlx42.mm_floor_img, 0, height);
}
	
void	set_dim(t_data *data)
{
	data->dim.dim_x = data->dim.max_x - data->dim.min_x + 1;
	data->dim.dim_y = data->dim.max_y - data->dim.min_y + 1;
}

void	create_wall_images(t_data *data)
{
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*west;

	north = mlx_load_png(data->textures.n_path);
	east = mlx_load_png(data->textures.e_path);
	south = mlx_load_png(data->textures.s_path);
	west = mlx_load_png(data->textures.w_path);
	data->mlx42.n_wall = mlx_texture_to_image(data->mlx42.mlx_ptr, north);
	data->mlx42.e_wall = mlx_texture_to_image(data->mlx42.mlx_ptr, east);
	data->mlx42.s_wall = mlx_texture_to_image(data->mlx42.mlx_ptr, south);
	data->mlx42.w_wall = mlx_texture_to_image(data->mlx42.mlx_ptr, west);
	mlx_delete_texture(north);
	mlx_delete_texture(east);
	mlx_delete_texture(south);
	mlx_delete_texture(west);
}

void	create_tiny_map(t_data *data)
{
	t_mlx42	mlx42;
	
	mlx42 = data->mlx42;
	mlx42.tiny_map = mlx_new_image(mlx42.mlx_ptr, TINY_MAPX, TINY_MAPY);
	ft_memset(mlx42.tiny_map->pixels, 255, 4 * TINY_MAPX * TINY_MAPX);
	mlx_image_to_window(mlx42.mlx_ptr, mlx42.tiny_map, 10, 10);
}

int	render_map(t_data *data)
{
	set_dim(data);
	data->mlx42.mlx_ptr = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	load_pics(data);
	// check_for_tile(data, draw_floor);
	// check_for_tile(data, which_picture);
	create_floor_ceiling_image(data);
	create_wall_images(data);
	create_image_player(data);
	create_tiny_map(data);
	mlx_loop_hook(data->mlx42.mlx_ptr, esc_hook, data->mlx42.mlx_ptr);
	mlx_loop_hook(data->mlx42.mlx_ptr, move_player, data);
	mlx_loop_hook(data->mlx42.mlx_ptr, draw_player, data);
	mlx_loop_hook(data->mlx42.mlx_ptr, draw_game, data);
	mlx_loop(data->mlx42.mlx_ptr);
	mlx_close_window(data->mlx42.mlx_ptr);
	mlx_terminate(data->mlx42.mlx_ptr);
	return (0);
}
