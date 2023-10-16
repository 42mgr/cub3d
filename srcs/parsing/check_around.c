/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_around.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:58:59 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/16 16:59:37 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks if only 1 or 0 can be found around the current positon ('1')
 * If not, the maze is not closed and the flood fill algorithm will fail
*/
int	check_around(t_data *data, int dxy[2][8], int x, int y)
{
	int				i;
	int				nx;
	int				ny;

	data->maze_cpy[y][x] = '1';
	i = 0;
	while (i < 8)
	{
		nx = x + dxy[0][i];
		ny = y + dxy[1][i];
		box_min_max(data, nx, ny);
		if (valid_i(data, nx, ny) != 0)
			return (1);
		if (data->maze_cpy[ny][nx] != '0' && data->maze_cpy[ny][nx] != '1')
			return (1);
		else
			i++;
	}
	return (0);
}

void	mm_draw_floor(t_data *data, int y, int x)
{
	if (x > (data->dim.max_x - data->dim.min_x + 1))
		return ;
	data->maze_cpy[y][x] = '1';
}

void	mm_draw_objects(t_data *data, int y, int x)
{
	if (x > (data->dim.max_x - data->dim.min_x + 1))
		return ;
	if (data->maze[y + data->dim.min_y][x + data->dim.min_x] == '1')
	{
		data->maze_cpy[y][x] = '1';
	}
	else if (data->maze[y + data->dim.min_y][x + data->dim.min_x] == '0')
	{
		data->maze_cpy[y][x] = '0';
	}
}
