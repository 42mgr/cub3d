/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 22:57:28 by fheld             #+#    #+#             */
/*   Updated: 2023/10/14 16:45:45 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * checks for a given position if in all four directions there is
 * WALL_SIZE amount of space left
 * returns 1 if the position is valid 0 if not
 * @param data the t_data pointer
 * @param pos the position to be checked for it's validity
*/
int	valid_pos(t_data *data, t_int_p2 pos)
{
	if ((pos.x - WALL_OFFSET) / SPRITE_SIZE >= 0 && \
		(pos.x - WALL_OFFSET) / SPRITE_SIZE < data->dim.dim_x && \
		(pos.y - WALL_OFFSET) / SPRITE_SIZE >= 0 && \
		(pos.y - WALL_OFFSET) / SPRITE_SIZE < data->dim.dim_y && \
		(pos.x + WALL_OFFSET) / SPRITE_SIZE >= 0 && \
		(pos.x + WALL_OFFSET) / SPRITE_SIZE < data->dim.dim_x && \
		(pos.y + WALL_OFFSET) / SPRITE_SIZE >= 0 && \
		(pos.y + WALL_OFFSET) / SPRITE_SIZE < data->dim.dim_y)
	{
		if (data->maze_cpy[(pos.y - WALL_OFFSET) / SPRITE_SIZE] \
			[pos.x / SPRITE_SIZE] == '0' && \
			data->maze_cpy[(pos.y + WALL_OFFSET) / SPRITE_SIZE] \
			[pos.x / SPRITE_SIZE] == '0' && \
			data->maze_cpy[pos.y / SPRITE_SIZE] \
			[(pos.x - WALL_OFFSET) / SPRITE_SIZE] == '0' && \
			data->maze_cpy[pos.y / SPRITE_SIZE] \
			[(pos.x + WALL_OFFSET) / SPRITE_SIZE] == '0')
		{
			return (1);
		}
	}
	return (0);
}

void	move_forward(t_data *data)
{
	t_int_p2	end_pos;

	end_pos.x = data->start.x - (5.0 * sin(data->start.dir / 180.0 * M_PI));
	end_pos.y = data->start.y - (5.0 * cos(data->start.dir / 180.0 * M_PI));
	if (valid_pos(data, end_pos) == 1)
	{
		data->start.x = end_pos.x;
		data->start.y = end_pos.y;
	}
}

void	move_backward(t_data *data)
{
	t_int_p2	end_pos;

	end_pos.x = data->start.x + (5.0 * sin(data->start.dir / 180.0 * M_PI));
	end_pos.y = data->start.y + (5.0 * cos(data->start.dir / 180.0 * M_PI));
	if (valid_pos(data, end_pos) == 1)
	{
		data->start.x = end_pos.x;
		data->start.y = end_pos.y;
	}
}

void	move_player(void *arg)
{
	t_data	*data;

	data = arg;
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_D))
		move_right(data);
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_A))
		move_left(data);
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_W))
		move_up(data);
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_S))
		move_down(data);
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_LEFT))
		data->start.dir = (data->start.dir + 2) % 360;
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_RIGHT))
		data->start.dir = (data->start.dir + 358) % 360;
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_UP))
		move_forward(data);
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_DOWN))
		move_backward(data);
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_H))
		data->mlx42.mm_player_img->enabled = \
			!data->mlx42.mm_player_img->enabled;
}