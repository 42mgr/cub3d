/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:08:37 by fheld             #+#    #+#             */
/*   Updated: 2023/10/13 16:04:21 by fheld            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
 * This fuction returns the position where a ray of given angle intersects
 * a horizontal wall the first time
 * @param data the t_data pointer
 * @param angle the angle in rad in which the ray is looking
*/
t_int_p2	horizontal_ray_collision(t_data *data, double angle)
{
	t_int_p2	end;

	if (angle > M_PI_2 * 3.0 || angle < M_PI_2)
		end = hrc_up(data, angle);
	else if (angle > M_PI_2 && angle < M_PI_2 * 3.0)
		end = hrc_down(data, angle);
	else if (angle == M_PI_2)
	{
		end.x = 0;
		end.y = data->start.y; 
	}
	else if (angle == M_PI_2 * 3)
	{
		end.x = (data->dim.dim_x - 1) * SPRITE_SIZE;
		end.y = data->start.y; 
	}
	else
	{
		end = (t_int_p2){2, 2};
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

/**
 * This fuction returns the position where a ray of given angle intersects
 * a vertical wall the first time
 * @param data the t_data pointer
 * @param angle the angle in rad in which the ray is looking
*/
t_int_p2	vertical_ray_collision(t_data *data, double angle)
{
	t_int_p2	end;

	if (angle > 0 && angle < M_PI)
		end = vrc_left(data, angle);
	else if (angle > M_PI && angle < 2.0 * M_PI)
		end = vrc_right(data, angle);
	else if (data->start.dir == 0)
	{
		end.x = data->start.x; 
		end.y = 0;
	}
	else if (data->start.dir == M_PI)
	{
		end.x = data->start.x; 
		end.y = (data->dim.dim_y - 1) * SPRITE_SIZE;
	}
	else
	{
		end = (t_int_p2){1, 1};
	}
	return (end);
}
