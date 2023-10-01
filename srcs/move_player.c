/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 22:57:28 by fheld             #+#    #+#             */
/*   Updated: 2023/10/01 22:58:00 by fheld            ###   ########.fr       */
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

void move_player(void* arg)
{
	t_data	*data;

	data = arg;
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_RIGHT))
		move_right(data);
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_LEFT))
		move_left(data);
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_UP))
		move_up(data);
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_DOWN))
		move_down(data);
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_A))
		data->start.dir++;
	if (mlx_is_key_down(data->mlx42.mlx_ptr, MLX_KEY_D))
		data->start.dir--;
}
