/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:08:37 by fheld             #+#    #+#             */
/*   Updated: 2023/10/14 17:49:14 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
