/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_directions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:45:22 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 16:45:50 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
