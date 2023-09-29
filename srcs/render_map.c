/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:10:50 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/29 09:08:34 by mgraf            ###   ########.fr       */
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
	load_texture(data->mlx42.mlx_ptr, &(data->mlx42.mm_black_img), "textures/mm_black.xpm42");
	load_texture(data->mlx42.mlx_ptr, &(data->mlx42.mm_grey_img), "textures/mm_black.xpm42");
	load_texture(data->mlx42.mlx_ptr, &(data->mlx42.mm_white_img), "textures/mm_black.xpm42");
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
	while (data->maze[y])
	{
		x = 0;
		while (data->maze[y][x])
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

int	render_map(t_data *data)
{
	data->mlx42.mlx_ptr = mlx_init(
			(data->dim.max_x - data->dim.min_x) * SPRITE_SIZE,
			(data->dim.max_y - data->dim.min_y) * SPRITE_SIZE, "Cub3D", true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	load_pics(data);
	check_for_tile(data, draw_floor);
	mlx_loop(data->mlx42.mlx_ptr);
	mlx_close_window(data->mlx42.mlx_ptr);
	mlx_terminate(data->mlx42.mlx_ptr);
	return (0);
}
