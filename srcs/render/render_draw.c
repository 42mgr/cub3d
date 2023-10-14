/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:51:58 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 16:55:50 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_picture(mlx_t *mlx_ptr, mlx_image_t *picture, int y, int x)
{
	mlx_image_to_window(mlx_ptr, picture, x, y);
}

void	check_for_tile(t_data *data, void (*f)(t_data *data, int, int))
{
	int	x;
	int	y;

	y = 0;
	while (data->maze[y + data->dim.min_y] && \
		y < data->dim.max_y - data->dim.min_y + 1)
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

/**
 * gets hooked into the mlx loop and draws the top down view of rays
 * hitting walls. (expects that the player image size is
 * at least (SPRITE_SIZE * dim_x) by (SPRITE_SIZE * dim_y) big, otherwise it
 * draws in illegal places
 * @param arg the void pointer to the data pointer struct
*/
	// int			ray_angle;
	// int i = 0;
	// ray_angle = ((data->start.dir + 23) % 360) * 10;
	// while (i < 460)
	// {
	// 	ray(data, ray_angle * M_PI / 1800.0);
	// 	ray_angle = (ray_angle + 3599) % 3600;
	// 	i++;
	// }
void	draw_player(void *arg)
{
	t_data		*data;

	data = arg;
	clear_image(data);
	return ;
}
