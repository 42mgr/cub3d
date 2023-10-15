/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:06:52 by fheld             #+#    #+#             */
/*   Updated: 2023/10/14 18:48:21 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * draws a vertical textured line on the image with given x coordinate,
 * where the corresponding ray has absolute angle 'angle"
 * @param data cub3d data pointer
 * @param x x coodinate on image where the line is drawn
 * @param angle the angle in which the ray goes,
 * measured counterclockwise in radiant with North being 0 radiant
*/
void	vertical_line(t_data *data, int x, double angle)
{
	t_int_p2	q;
	t_int_p2	p;
	double		dist_to_q;
	double		dist_to_p;
	double		fish;

	q = horizontal_ray_collision(data, angle);
	p = vertical_ray_collision(data, angle);
	dist_to_p = dist((t_int_p2){data->start.x, data->start.y}, p);
	dist_to_q = dist((t_int_p2){data->start.x, data->start.y}, q);
	fish = cos((data->start.dir * M_PI / 180.0) - angle);
	if (dist_to_p >= dist_to_q || isnan(dist_to_p) == 1)
	{
		if (angle < M_PI / 2.0 || angle > M_PI * 3.0 / 2.0)
			draw_vertical_texture_s(data, x, 60000.0 / (dist_to_q * fish), q);
		else
			draw_vertical_texture_n(data, x, 60000.0 / (dist_to_q * fish), q);
	}
	else if (dist_to_p < dist_to_q)
	{
		if (angle < M_PI)
			draw_vertical_texture_e(data, x, 60000.0 / (dist_to_p * fish), p);
		else
			draw_vertical_texture_w(data, x, 60000.0 / (dist_to_p * fish), p);
	}
}

/**
 * function that is hooked in the mlx loop and draws the textured walls
 * (but not the monocolored background)
 * @param arg void pointer to the t_data data struct
*/
void	draw_game(void *arg)
{
	int			i;
	t_data		*data;
	double		ray_angle;
	int			field_of_view;

	i = 0;
	field_of_view = WINDOW_WIDTH / 20;
	data = arg;
	ray_angle = data->start.dir * M_PI / 180.0;
	ray_angle += field_of_view * M_PI / 360.0;
	while (i < field_of_view * 20)
	{
		if (ray_angle >= 2.0 * M_PI)
			ray_angle -= 2.0 * M_PI;
		else if (ray_angle < 0)
			ray_angle += 2.0 * M_PI;
		vertical_line(data, i, ray_angle);
		ray_angle -= 0.000875;
		i++;
	}
	return ;
}
