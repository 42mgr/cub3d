/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:10:50 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/28 22:54:00 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	data->mlx42.mm_black = mlx_load_xpm42("./textures/mm_black.xpm");
	data->mlx42.mm_grey = mlx_load_xpm42("./textures/mm_grey.xpm");
	data->mlx42.mm_white = mlx_load_xpm42("./textures/mm_white.xpm");
	data->mlx42.mm_black = mlx_texture_to_image(data->mlx42.mm_black);
	data->mlx42.mm_grey = mlx_texture_to_image(data->mlx42.mm_grey);
	data->mlx42.mm_white = mlx_texture_to_image(data->mlx42.mm_white);
	check_for_tile(data, draw_floor);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_loop(data->mlx42.mlx_ptr);
	mlx_close_window(data->mlx42.mlx_ptr);
	mlx_terminate(data->mlx42.mlx_ptr);
	return (0);
}
