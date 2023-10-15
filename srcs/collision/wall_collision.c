/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:47:32 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 17:49:18 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 * This fuction returns the position where a ray looking upwards
 * of given angle intersects a horizontal wall the first time
 * @param data the t_data pointer
 * @param angle the angle in rad in which the ray is looking
 * hrc is an acronym for horizontal ray collison
*/
t_int_p2	hrc_up(t_data *data, double angle)
{
	t_int_p2	end;
	int			i;

	i = 0;
	while (1 && i < 1000)
	{
		end.y = ((data->start.y / SPRITE_SIZE) - i) * SPRITE_SIZE;
		end.x = data->start.x - tan(angle) * (data->start.y - end.y);
		if (end.y / SPRITE_SIZE - 1 < 0 || \
			end.y / SPRITE_SIZE - 1 >= data->dim.dim_y)
			break ;
		if (end.x / SPRITE_SIZE < 0 || \
			end.x / SPRITE_SIZE >= data->dim.dim_x)
			break ;
		if (data->maze_cpy[\
			end.y / SPRITE_SIZE - 1][(end.x / SPRITE_SIZE)] == '1')
			break ;
		i++;
	}
	return (end);
}

/**
 * This fuction returns the position where a ray looking downwards
 * of given angle intersects a horizontal wall the first time
 * @param data the t_data pointer
 * @param angle the angle in rad in which the ray is looking
 * hrc is an acronym for horizontal ray collison
*/
t_int_p2	hrc_down(t_data *data, double angle)
{
	t_int_p2	end;
	int			i;

	i = 0;
	while (1 && i < 1000)
	{
		end.y = ((data->start.y / SPRITE_SIZE) + 1 + i) * SPRITE_SIZE;
		end.x = data->start.x - tan((angle - M_PI)) * (data->start.y - end.y);
		if (end.y / SPRITE_SIZE < 0 || end.y / SPRITE_SIZE >= data->dim.dim_y)
			break ;
		if (end.x / SPRITE_SIZE < 0 || end.x / SPRITE_SIZE >= data->dim.dim_x)
			break ;
		if (data->maze_cpy[(end.y / SPRITE_SIZE)][(end.x / SPRITE_SIZE)] == '1')
			break ;
		i++;
	}
	return (end);
}

/**
 * This fuction returns the position where a ray looking to the left
 * of given angle intersects a vertical wall the first time
 * @param data the t_data pointer
 * @param angle the angle in rad in which the ray is looking
 * vrc is an acronym for vertical ray collison
*/
t_int_p2	vrc_left(t_data *data, double angle)
{
	t_int_p2	end;
	int			i;

	i = 0;
	while (1 && i < 1000)
	{
		end.x = (data->start.x / SPRITE_SIZE - i) * SPRITE_SIZE;
		end.y = data->start.y - tan(M_PI / 2.0 - angle) * \
			(data->start.x - end.x);
		if (end.y / SPRITE_SIZE < 0 || end.y / SPRITE_SIZE >= data->dim.dim_y)
			break ;
		if (end.x / SPRITE_SIZE - 1 < 0 || \
			end.x / SPRITE_SIZE - 1 >= data->dim.dim_x)
			break ;
		if (data->maze_cpy[\
			(end.y / SPRITE_SIZE)][(end.x / SPRITE_SIZE) - 1] == '1')
			break ;
		i++;
	}
	return (end);
}

/**
 * This fuction returns the position where a ray looking to the right
 * of given angle intersects a vertical wall the first time
 * @param data the t_data pointer
 * @param angle the angle in rad in which the ray is looking
 * vrc is an acronym for vertical ray collison
*/
t_int_p2	vrc_right(t_data *data, double angle)
{
	t_int_p2	end;
	int			i;

	i = 0;
	while (1 && i < 1000)
	{
		end.x = (data->start.x / SPRITE_SIZE + 1 + i) * SPRITE_SIZE;
		end.y = data->start.y - tan(angle - (M_PI / 2.0 * 3.0)) * \
			(end.x - data->start.x);
		if (end.y / SPRITE_SIZE < 0 || end.y / SPRITE_SIZE >= data->dim.dim_y)
			break ;
		if (end.x / SPRITE_SIZE < 0 || end.x / SPRITE_SIZE >= data->dim.dim_x)
			break ;
		if (data->maze_cpy[end.y / SPRITE_SIZE][end.x / SPRITE_SIZE] == '1')
			break ;
		i++;
	}
	return (end);
}
