/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:10:50 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/01 10:26:07 by mgraf            ###   ########.fr       */
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

void move_player(void* arg)
{
	t_data	*data;

	data = arg;
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_RIGHT))
		data->start.x++;
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_LEFT))
		data->start.x--;
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_UP))
		data->start.y--;
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_DOWN))
		data->start.y++;
}

void draw_player(void* arg)
{
	t_data	*data;

	data = arg;
	data->mlx42.mm_player_img = mlx_new_image(data->mlx42.mlx_ptr, \
		(data->dim.max_x - data->dim.min_x + 1) * SPRITE_SIZE, \
		(data->dim.max_y - data->dim.min_y + 1) * SPRITE_SIZE);
	mlx_image_to_window(data->mlx42.mlx_ptr, data->mlx42.mm_player_img, 0, 0);
	mlx_put_pixel(data->mlx42.mm_player_img, data->start.x, data->start.y, 0xFFFF00FF);
}

int	render_map(t_data *data)
{
	data->mlx42.mlx_ptr = mlx_init(
			(data->dim.max_x - data->dim.min_x + 1) * SPRITE_SIZE,
			(data->dim.max_y - data->dim.min_y + 1) * SPRITE_SIZE, "Cub3D", true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	load_pics(data);
	check_for_tile(data, draw_floor);
	check_for_tile(data, which_picture);
	mlx_loop_hook(data->mlx42.mlx_ptr, esc_hook, data->mlx42.mlx_ptr);
	mlx_loop_hook(data->mlx42.mlx_ptr, move_player, data);
	mlx_loop_hook(data->mlx42.mlx_ptr, draw_player, data);
	mlx_loop(data->mlx42.mlx_ptr);
	mlx_close_window(data->mlx42.mlx_ptr);
	mlx_terminate(data->mlx42.mlx_ptr);
	return (0);
}
