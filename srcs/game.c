/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:06:52 by fheld             #+#    #+#             */
/*   Updated: 2023/10/09 14:52:22 by fheld            ###   ########.fr       */
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

/**
 * draws a vertical sclice through the center of the screen
 * @param data the cub3d data pointer
 * @param x the x-coordinate on which the slcie is
 * @param height the height of the slice
 * @param loc is the location where the intersection happens
*/
void	draw_vertical_texture_1(t_data *data, int x, int height, t_int_p2 loc)
{
	t_int_p2	top;
	t_int_p2	bottom;
	int			pos_in_img;

	pos_in_img = loc.x % SPRITE_SIZE;
	if (height < 0 || x < 0 || x > data->mlx42.mlx_ptr->width)
		return ;
	// if (height > data->mlx42.mlx_ptr->height - 100)
	// 	height = data->mlx42.mlx_ptr->height - 100;
	top.x = x;
	top.y = (data->dim.dim_y * SPRITE_SIZE / 2) - (height / 2);
	bottom.x = x;
	bottom.y = (data->dim.dim_y * SPRITE_SIZE / 2) + (height / 2);
	
	// tmp rewrite needed
	int	i = 0;
	int d = bottom.y - top.y;
	int	s = data->mlx42.n_wall->width * pos_in_img / SPRITE_SIZE; 
	uint32_t pxl;
	
	uint8_t	*a = data->mlx42.n_wall->pixels;
	mlx_put_pixel(data->mlx42.n_wall, 0, 0, 0x12345678);
	printf("%x, %x, %x, %x\n", a[0], a[1], a[2], a[3]);
	while (i < d)
	{
		pxl = 0x000000FF;
		pxl += data->mlx42.n_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 2] * 0x0000100;
		pxl += data->mlx42.n_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 1] * 0x0010000;
		pxl += data->mlx42.n_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 0] * 0x1000000;
		if (top.y + i >= 50 && top.y + i < data->mlx42.mlx_ptr->height - 50)
			mlx_put_pixel(data->mlx42.mm_player_img, x, top.y + i, pxl);
		i++;
	}
}

void	tmp_lines(t_data *data, int x, double angle)
{
	t_int_p2	q;
	t_int_p2	p;
	double		dist_to_q;
	double		dist_to_p;
	
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
			draw_vertical_texture_1(data, x, 60000.0 / (dist_to_q * \
				cos((data->start.dir * M_PI / 180.0) - angle)), q);
			// draw_vertical_line(data, x, 60000.0 / (dist_to_q * \
				// cos((data->start.dir * M_PI / 180.0) - angle)), GREY_B);
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
	double			ray_angle;
	
	data = arg;
	int i = 0;
	ray_angle = data->start.dir * M_PI / 180.0;
	ray_angle += 0.401;
	while (i < 460)
	{
		if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
		tmp_lines(data, i + 20, ray_angle);
		ray_angle -= 0.00175;
		i++;
	}
	//debug_screen(data);
	return ;
}