/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:06:52 by fheld             #+#    #+#             */
/*   Updated: 2023/10/12 13:44:51 by fheld            ###   ########.fr       */
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
 * draws a vertical sclice through the center of the screen in case the ray goes north
 * @param data the cub3d data pointer
 * @param x the x-coordinate on which the slice is
 * @param d the height of the slice
 * @param loc is the location where the intersection happens
*/
void	draw_vertical_texture_n(t_data *data, int x, int d, t_int_p2 loc)
{
	int			i;
	int			s;
	uint32_t 	pxl;
	t_int_p2	top;
	int			pos_in_img;

	i = 0;
	pos_in_img = loc.x % SPRITE_SIZE;
	if (d < 0 || x < 0 || x > data->mlx42.mlx_ptr->width)
		return ;
	top.y = (WINDOW_HEIGHT / 2) - (d / 2);
	s = data->mlx42.n_wall->width * pos_in_img / SPRITE_SIZE; 
	while (i < d)
	{
		pxl = TRA_Y;
		pxl += data->mlx42.n_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 2] * 0x0000100;
		pxl += data->mlx42.n_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 1] * 0x0010000;
		pxl += data->mlx42.n_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 0] * 0x1000000;
		if (top.y + i >= 50 && top.y + i < data->mlx42.mlx_ptr->height - 50)
			mlx_put_pixel(data->mlx42.mm_player_img, x, top.y + i, pxl);
		i++;
	}
}

/**
 * draws vertical textured line in the case the ray is looking to east
 * @param data cub3d data pointer
 * @param x x coodinate on image where the line is drawn
 * @param d height in pixels of the vertical line
 * @param loc the location where the ray hit the wall 
 * (needed to determine where in the texure we are, e.g. in the middle of it)
*/
void	draw_vertical_texture_e(t_data *data, int x, int d, t_int_p2 loc)
{
	int			i;
	int			s;
	uint32_t 	pxl;
	t_int_p2	top;
	int			pos_in_img;

	i = 0;
	pos_in_img = loc.y % SPRITE_SIZE;
	if (d < 0 || x < 0 || x > data->mlx42.mlx_ptr->width)
		return ;
	top.y = (WINDOW_HEIGHT / 2) - (d / 2);
	s = data->mlx42.e_wall->width * pos_in_img / SPRITE_SIZE; 
	while (i < d)
	{
		pxl = TRA_Y;
		pxl += data->mlx42.e_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 2] * 0x0000100;
		pxl += data->mlx42.e_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 1] * 0x0010000;
		pxl += data->mlx42.e_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 0] * 0x1000000;
		if (top.y + i >= 50 && top.y + i < data->mlx42.mlx_ptr->height - 50)
			mlx_put_pixel(data->mlx42.mm_player_img, x, top.y + i, pxl);
		i++;
	}
}

/**
 * draws vertical textured line in the case the ray is looking to south
 * @param data cub3d data pointer
 * @param x x coodinate on image where the line is drawn
 * @param d height in pixels of the vertical line
 * @param loc the location where the ray hit the wall 
 * (needed to determine where in the texure we are, e.g. in the middle of it)
*/
void	draw_vertical_texture_s(t_data *data, int x, int d, t_int_p2 loc)
{
	int			i;
	int			s;
	uint32_t 	pxl;
	t_int_p2	top;
	int			pos_in_img;

	i = 0;
	pos_in_img = loc.x % SPRITE_SIZE;
	if (d < 0 || x < 0 || x > data->mlx42.mlx_ptr->width)
		return ;
	top.y = (WINDOW_HEIGHT / 2) - (d / 2);
	s = data->mlx42.s_wall->width * pos_in_img / SPRITE_SIZE; 
	while (i < d)
	{
		pxl = TRA_Y;
		pxl += data->mlx42.s_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 2] * 0x0000100;
		pxl += data->mlx42.s_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 1] * 0x0010000;
		pxl += data->mlx42.s_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 0] * 0x1000000;
		if (top.y + i >= 50 && top.y + i < data->mlx42.mlx_ptr->height - 50)
			mlx_put_pixel(data->mlx42.mm_player_img, x, top.y + i, pxl);
		i++;
	}
}

/**
 * draws vertical textured line in the case the ray is looking to west
 * @param data cub3d data pointer
 * @param x x coodinate on image where the line is drawn
 * @param d height in pixels of the vertical line
 * @param loc the location where the ray hit the wall 
 * (needed to determine where in the texure we are, e.g. in the middle of it)
*/
void	draw_vertical_texture_w(t_data *data, int x, int d, t_int_p2 loc)
{
	int			i;
	int			s;
	uint32_t 	pxl;
	t_int_p2	top;
	int			pos_in_img;

	i = 0;
	pos_in_img = loc.y % SPRITE_SIZE;
	if (d < 0 || x < 0 || x > data->mlx42.mlx_ptr->width)
		return ;
	top.y = (WINDOW_HEIGHT / 2) - (d / 2);
	s = data->mlx42.w_wall->width * pos_in_img / SPRITE_SIZE; 
	while (i < d)
	{
		pxl = TRA_Y;
		pxl += data->mlx42.w_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 2] * 0x0000100;
		pxl += data->mlx42.w_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 1] * 0x0010000;
		pxl += data->mlx42.w_wall->pixels[(4 * 32 * s) + 4*(i*32/d) + 0] * 0x1000000;
		if (top.y + i >= 50 && top.y + i < data->mlx42.mlx_ptr->height - 50)
			mlx_put_pixel(data->mlx42.mm_player_img, x, top.y + i, pxl);
		i++;
	}
}

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
	if ((q.x == 0 && q.y == 0) || (p.x == 0 && p.y == 0))
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, p, L_RED);
	else if (dist_to_p >= dist_to_q || isnan(dist_to_p) == 1)
		if (angle < M_PI / 2.0 || angle > M_PI *3.0 / 2.0)
			draw_vertical_texture_s(data, x, 60000.0 / (dist_to_q * fish), q);
		else
			draw_vertical_texture_n(data, x, 60000.0 / (dist_to_q * fish), q);
	else
		if (angle < M_PI)
			draw_vertical_texture_e(data, x, 60000.0 / (dist_to_p * fish), p);
		else
			draw_vertical_texture_w(data, x, 60000.0 / (dist_to_p * fish), p);
}

void	draw_game(void *arg)
{
	t_data		*data;
	double			ray_angle;
	
	data = arg;
	int i = 0;
	ray_angle = data->start.dir * M_PI / 180.0;
	ray_angle += 0.401; 
	while (i < 920)
	{
		if (ray_angle >= 2.0 * M_PI)
			ray_angle -= 2.0 * M_PI;
		else if (ray_angle < 0)
			ray_angle += 2.0 * M_PI;
		vertical_line(data, i + 20, ray_angle);
		ray_angle -= 0.000875;
		i++;
	}
	//debug_screen(data);
	return ;
}