/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:06:52 by fheld             #+#    #+#             */
/*   Updated: 2023/10/04 21:18:42 by fheld            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * draws a vertical line through the center of the screen
 * @param data the cub3d data pointer
 * @param x the x-coordinate on which the line is
 * @param height the height of the line
*/
void	draw_vertical_line(t_data *data, int x, int height, int color)
{
	t_int_p2	top;
	t_int_p2	bottom;

	top.x = x;
	top.y = (data->dim.dim_y * SPRITE_SIZE / 2) - (height / 2);
	bottom.x = x;
	bottom.y = (data->dim.dim_y * SPRITE_SIZE / 2) + (height / 2);
	draw_line(data, top, bottom, color);
}


void	tmp_lines(t_data *data, int x)
{
	t_int_p2	q;
	t_int_p2	p;
	float		dist_to_q;
	float		dist_to_p;
	
	q = horizontal_ray_collision(data);
	p = vertical_ray_collision(data);
	dist_to_p = dist((t_int_p2){data->start.x, data->start.y}, p);
	dist_to_q = dist((t_int_p2){data->start.x, data->start.y}, q);
	if (q.x == 0 && q.y == 0)
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, p, L_RED);
	else if (p.x == 0 && p.y == 0)
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, p, L_RED);
	else if (dist_to_p > dist_to_q)
		draw_vertical_line(data, x, (40000.0 / dist_to_q), L_GREEN);
	else
		draw_vertical_line(data, x, (40000.0 / dist_to_p), L_RED);
}

void	draw_game(void *arg)
{
	t_data		*data;

	data = arg;
	int i = 0;
	data->start.dir = (data->start.dir + 23) % 360;
	while (i < 46)
	{
		tmp_lines(data, i * 10 + 20);
		data->start.dir = (data->start.dir + 359) % 360;
		i++;
	}
	data->start.dir = (data->start.dir + 23) % 360;
	return ;
}