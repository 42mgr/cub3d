/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 22:57:28 by fheld             #+#    #+#             */
/*   Updated: 2023/10/04 17:15:52 by fheld            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * checks if moving up would collide with the wall, if not moves one step
*/
void	move_up(t_data *data)
{
	if (data->maze_cpy[(data->start.y - WALL_OFFSET) / SPRITE_SIZE] \
		[data->start.x / SPRITE_SIZE] == '0')
		data->start.y--;
}

void	move_down(t_data *data)
{
	if (data->maze_cpy[(data->start.y + WALL_OFFSET) / SPRITE_SIZE] \
		[data->start.x / SPRITE_SIZE] == '0')
		data->start.y++;
}

void	move_left(t_data *data)
{
	if (data->maze_cpy[data->start.y / SPRITE_SIZE] \
		[(data->start.x - WALL_OFFSET) / SPRITE_SIZE] == '0')
		data->start.x--;
}

void	move_right(t_data *data)
{
	if (data->maze_cpy[data->start.y / SPRITE_SIZE] \
		[(data->start.x + WALL_OFFSET) / SPRITE_SIZE] == '0')
		data->start.x++;
}

// todo: factor out the long if condition
void	move_forward(t_data *data)
{
	t_int_p2	end_pos;

	end_pos.x = data->start.x - (5.0 * sin(data->start.dir / 180.0 * M_PI));
	end_pos.y = data->start.y - (5.0 * cos(data->start.dir / 180.0 * M_PI));

	if (end_pos.x / SPRITE_SIZE >= 0 && \
		end_pos.x / SPRITE_SIZE < data->dim.dim_x && \
		end_pos.y / SPRITE_SIZE >= 0 &&  \
		end_pos.y / SPRITE_SIZE < data->dim.dim_y)
		if (data->maze_cpy[end_pos.y / SPRITE_SIZE] \
			[end_pos.x / SPRITE_SIZE] == '0')
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

	if (end_pos.x / SPRITE_SIZE >= 0 && \
		end_pos.x / SPRITE_SIZE < data->dim.dim_x && \
		end_pos.y / SPRITE_SIZE >= 0 &&  \
		end_pos.y / SPRITE_SIZE < data->dim.dim_y)
		if (data->maze_cpy[end_pos.y / SPRITE_SIZE] \
			[end_pos.x / SPRITE_SIZE] == '0')
		{
			data->start.x = end_pos.x;
			data->start.y = end_pos.y;
		}
}

void move_player(void* arg)
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
		data->start.dir = (data->start.dir + 1) % 360;
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_RIGHT))
		data->start.dir = (data->start.dir + 359) % 360;
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_UP))
		move_forward(data);
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_DOWN))
		move_backward(data);
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_H))
		data->mlx42.mm_player_img->enabled = !data->mlx42.mm_player_img->enabled;
}
