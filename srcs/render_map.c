/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:10:50 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/03 19:14:32 by fheld            ###   ########.fr       */
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
/* 	printf("y: %d, x: %d value: %c\n", y, x, data->maze[y + data->dim.min_y][x + data->dim.min_x]);
	(void)data; */
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

void	draw_fan(t_data *data)
{
	int	i;

	// i = -20;
	i = 0;
	while (i < 1)
	{
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, \
			(t_int_p2){data->start.x - 50 * sin((data->start.dir + i)/180.0*M_PI), \
			data->start.y - 50 * cos((data->start.dir + i)/180.0*M_PI)}, 0x000000FF);
		i+=5;
	}
}

// no idea why we need the last 4 multipier
void draw_player(void* arg)
{
	t_data	*data;

	data = arg;
	ft_memset(data->mlx42.mm_player_img->pixels, 0x00, sizeof(uint8_t) * \
		data->dim.dim_x * SPRITE_SIZE * data->dim.dim_y * SPRITE_SIZE * 4);

	t_int_p2 p = horizontal_ray_collision(data);
	// t_int_p2 p = vertical_ray_collision(data);
	// data->maze_cpy[(p.y/SPRITE_SIZE)][(p.x/SPRITE_SIZE)]
	printf("p coordinates: x = %d, y = %d, maze_cpy[][] = %c\n", p.x, p.y, 99);
	printf("p.y/SPRITE_SIZE = %d, p.x/SPRITE_SIZE = %d, start.dir = %d\n", p.y/SPRITE_SIZE, p.x/SPRITE_SIZE, data->start.dir);
	draw_fan(data);
	// draw_line(data, (t_int_p2){data->start.x, data->start.y}, q, L_BLUE);
	draw_line(data, (t_int_p2){data->start.x, data->start.y}, p, L_RED);
	mlx_put_pixel(data->mlx42.mm_player_img, data->start.x, data->start.y, 0x000000FF);
	mlx_put_pixel(data->mlx42.mm_player_img, 10, 100, 0xFF0000FF);
}

void	set_dim(t_data *data)
{
	data->dim.dim_x = data->dim.max_x - data->dim.min_x + 1;
	data->dim.dim_y = data->dim.max_y - data->dim.min_y + 1;
}

int	render_map(t_data *data)
{
	set_dim(data);
	data->mlx42.mlx_ptr = mlx_init(data->dim.dim_x * SPRITE_SIZE, \
			data->dim.dim_y * SPRITE_SIZE, "Cub3D", true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	load_pics(data);
	check_for_tile(data, draw_floor);
	check_for_tile(data, which_picture);
	mlx_put_pixel(data->mlx42.mm_white_img, 63, 63, 0x000000FF);
	create_image_player(data);
	mlx_loop_hook(data->mlx42.mlx_ptr, esc_hook, data->mlx42.mlx_ptr);
	mlx_loop_hook(data->mlx42.mlx_ptr, move_player, data);
	mlx_loop_hook(data->mlx42.mlx_ptr, draw_player, data);
	mlx_loop(data->mlx42.mlx_ptr);
	mlx_close_window(data->mlx42.mlx_ptr);
	mlx_terminate(data->mlx42.mlx_ptr);
	return (0);
}
