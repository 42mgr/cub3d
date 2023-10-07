/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:06:52 by fheld             #+#    #+#             */
/*   Updated: 2023/10/07 15:13:47 by fheld            ###   ########.fr       */
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

	if (height < 0 || x < 0 || x > data->mlx42.mlx_ptr->width)
		return ;
	if (height > data->mlx42.mlx_ptr->height - 100)
		height = data->mlx42.mlx_ptr->height - 100;
	top.x = x;
	top.y = (data->dim.dim_y * SPRITE_SIZE / 2) - (height / 2);
	bottom.x = x;
	bottom.y = (data->dim.dim_y * SPRITE_SIZE / 2) + (height / 2);
	draw_line(data, top, bottom, color);
}

void	tmp_lines(t_data *data, int x, float angle)
{
	t_int_p2	q;
	t_int_p2	p;
	float		dist_to_q;
	float		dist_to_p;
	
	q = horizontal_ray_collision(data, angle);
	p = vertical_ray_collision(data, angle);
	dist_to_p = dist((t_int_p2){data->start.x, data->start.y}, p);
	dist_to_q = dist((t_int_p2){data->start.x, data->start.y}, q);
	if (q.x == 0 && q.y == 0)
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, p, L_RED);
	else if (p.x == 0 && p.y == 0)
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, p, L_RED);
	else if (dist_to_p >= dist_to_q || isnan(dist_to_p) == 1)
		if (angle < M_PI / 2.0 || angle > M_PI *3.0 / 2.0)
			draw_vertical_line(data, x, 60000.0 / (dist_to_q * \
				cos((data->start.dir * M_PI / 180.0) - angle)), GREY_A);
		else
			draw_vertical_line(data, x, 60000.0 / (dist_to_q * \
				cos((data->start.dir * M_PI / 180.0) - angle)), GREY_B);
	else
	{
		if (angle < M_PI)
			draw_vertical_line(data, x, 60000.0 / (dist_to_p * \
				cos((data->start.dir * M_PI / 180.0) - angle)), GREY_C);
		else
			draw_vertical_line(data, x, 60000.0 / (dist_to_p * \
				cos((data->start.dir * M_PI / 180.0) - angle)), GREY_D);	
	}
}

void	draw_game(void *arg)
{
	t_data		*data;
	int			ray_angle;
	
	data = arg;
	int i = 0;
	ray_angle = ((data->start.dir + 23) % 360) * 10;

	while (i < 460)
	{
		tmp_lines(data, i + 20, ray_angle * M_PI / 1800.0);
		ray_angle = (ray_angle + 3599) % 3600;
		i++;
	}
	//debug_screen(data);
	return ;
}