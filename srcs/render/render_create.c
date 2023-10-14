/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:50:19 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 17:00:59 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 * loads the four wall textures and makes mlx_image_t's out of them
 * @param data the t_data pointer
*/
int	create_wall_images(t_data *data)
{
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*west;

	north = mlx_load_png(data->textures.n_path);
	east = mlx_load_png(data->textures.e_path);
	south = mlx_load_png(data->textures.s_path);
	west = mlx_load_png(data->textures.w_path);
	if ((north && east && south && west) == 0)
	{
		delete_four_textures(north, east, south, west);
		return (1);
	}
	data->mlx42.n_wall = mlx_texture_to_image(data->mlx42.mlx_ptr, north);
	data->mlx42.e_wall = mlx_texture_to_image(data->mlx42.mlx_ptr, east);
	data->mlx42.s_wall = mlx_texture_to_image(data->mlx42.mlx_ptr, south);
	data->mlx42.w_wall = mlx_texture_to_image(data->mlx42.mlx_ptr, west);
	delete_four_textures(north, east, south, west);
	return (0);
}

/**
 * in progress mini map shown on the top left
 * @param data the t_data pointer
 * @return 0 if everything is sucessful, 1 on error
*/
int	create_tiny_map(t_data *data)
{
	t_mlx42	mlx42;

	mlx42 = data->mlx42;
	mlx42.tiny_map = mlx_new_image(mlx42.mlx_ptr, TINY_MAPX, TINY_MAPY);
	if (mlx42.tiny_map == NULL)
		return (1);
	ft_memset(mlx42.tiny_map->pixels, 255, 4 * TINY_MAPX * TINY_MAPX);
	if (mlx_image_to_window(mlx42.mlx_ptr, mlx42.tiny_map, 10, 10) == -1)
		return (1);
	return (0);
}

/**
 * created two images and fills them with the respective solid color that is
 * given in the data struct. These images are then in the background and
 * act as floor and ceiling
 * @param data the t_data pointer
 * @return 0 on sucess, 1 on failiure
*/
int	create_floor_ceiling_image(t_data *data)
{
	mlx_t	*mlx;
	int		height;
	int		width;

	mlx = data->mlx42.mlx_ptr;
	height = WINDOW_HEIGHT / 2;
	width = WINDOW_WIDTH;
	data->mlx42.mm_floor_img = \
		mlx_new_image(data->mlx42.mlx_ptr, width, height);
	data->mlx42.mm_ceiling_img = \
		mlx_new_image(data->mlx42.mlx_ptr, width, height);
	if (data->mlx42.mm_floor_img == NULL || data->mlx42.mm_ceiling_img == NULL)
		return (1);
	fill_ceiling(data);
	fill_floor(data);
	if (mlx_image_to_window(mlx, data->mlx42.mm_ceiling_img, 0, 0) == -1)
		return (1);
	if (mlx_image_to_window(mlx, data->mlx42.mm_floor_img, 0, height) == -1)
		return (1);
	return (0);
}

/*	data->mlx42.mm_player_img = mlx_new_image(data->mlx42.mlx_ptr,
		(data->dim.max_x - data->dim.min_x + 1) * SPRITE_SIZE,
		(data->dim.max_y - data->dim.min_y + 1) * SPRITE_SIZE); */
/**
 * creates new image where the game is drawn on (size is given by defines)
 * sets inital position of player to be in the middle of it's starting square
 * puts image to window
 * @param data t_data pointer
 * @return 0 on success 1 on fail
*/
int	create_image_player(t_data *data)
{
	data->start.x = \
		(data->start.x - data->dim.min_x) * SPRITE_SIZE + (SPRITE_SIZE / 2);
	data->start.y = \
		(data->start.y - data->dim.min_y) * SPRITE_SIZE + (SPRITE_SIZE / 2);
	data->mlx42.mm_player_img = \
		mlx_new_image(data->mlx42.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->mlx42.mm_player_img == NULL)
		return (1);
	if (mlx_image_to_window(data->mlx42.mlx_ptr, \
		data->mlx42.mm_player_img, 0, 0) == -1)
		return (1);
	return (0);
}
