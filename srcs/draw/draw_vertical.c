/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:40:15 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 16:40:49 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
 * draws a vertical sclice through the center of the screen in
 * case the ray goes north
 * @param data the cub3d data pointer
 * @param x the x-coordinate on which the slice is
 * @param d the height of the slice
 * @param loc is the location where the intersection with the wall happens
*/
void	draw_vertical_texture_n(t_data *data, int x, int d, t_int_p2 loc)
{
	int			i;
	uint32_t	pxl;
	t_int_p2	top;
	int			pos_in_wall;
	int			pos_in_texture;

	i = 0;
	pos_in_wall = loc.x % SPRITE_SIZE;
	if (d < 0 || x < 0 || x > (int)data->mlx42.mm_player_img->width)
		return ;
	top.y = (WINDOW_HEIGHT / 2) - (d / 2);
	pos_in_texture = data->mlx42.n_wall->height * pos_in_wall / SPRITE_SIZE;
	while (i < d)
	{
		pxl = TRA_Y;
		pxl += data->mlx42.n_wall->pixels[(4 * data->mlx42.n_wall->width * \
pos_in_texture) + 4 * (i * data->mlx42.n_wall->height / d) + 2] * 0x0000100;
		pxl += data->mlx42.n_wall->pixels[(4 * data->mlx42.n_wall->width * \
pos_in_texture) + 4 * (i * data->mlx42.n_wall->height / d) + 1] * 0x0010000;
		pxl += data->mlx42.n_wall->pixels[(4 * data->mlx42.n_wall->width * \
pos_in_texture) + 4 * (i * data->mlx42.n_wall->height / d) + 0] * 0x1000000;
		if (top.y + i >= 0 && top.y + i < WINDOW_HEIGHT)
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
	uint32_t	pxl;
	t_int_p2	top;
	int			pos_in_texture;
	int			pos_in_wall;

	i = 0;
	pos_in_wall = loc.y % SPRITE_SIZE;
	if (d < 0 || x < 0 || x > (int)data->mlx42.mm_player_img->width)
		return ;
	top.y = (WINDOW_HEIGHT / 2) - (d / 2);
	pos_in_texture = data->mlx42.e_wall->height * pos_in_wall / SPRITE_SIZE;
	while (i < d)
	{
		pxl = TRA_Y;
		pxl += data->mlx42.e_wall->pixels[(4 * data->mlx42.e_wall->width * \
pos_in_texture) + 4 * (i * data->mlx42.e_wall->height / d) + 2] * 0x0000100;
		pxl += data->mlx42.e_wall->pixels[(4 * data->mlx42.e_wall->width * \
pos_in_texture) + 4 * (i * data->mlx42.e_wall->height / d) + 1] * 0x0010000;
		pxl += data->mlx42.e_wall->pixels[(4 * data->mlx42.e_wall->width * \
pos_in_texture) + 4 * (i * data->mlx42.e_wall->height / d) + 0] * 0x1000000;
		if (top.y + i >= 0 && top.y + i < WINDOW_HEIGHT)
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
	uint32_t	pxl;
	t_int_p2	top;
	int			pos_in_texture;
	int			pos_in_wall;

	i = 0;
	pos_in_wall = loc.x % SPRITE_SIZE;
	if (d < 0 || x < 0 || x > (int)data->mlx42.mm_player_img->width)
		return ;
	top.y = (WINDOW_HEIGHT / 2) - (d / 2);
	pos_in_texture = data->mlx42.s_wall->height * pos_in_wall / SPRITE_SIZE;
	while (i < d)
	{
		pxl = TRA_Y;
		pxl += data->mlx42.s_wall->pixels[(4 * data->mlx42.s_wall->width * \
pos_in_texture) + 4 * (i * data->mlx42.s_wall->height / d) + 2] * 0x0000100;
		pxl += data->mlx42.s_wall->pixels[(4 * data->mlx42.s_wall->width * \
pos_in_texture) + 4 * (i * data->mlx42.s_wall->height / d) + 1] * 0x0010000;
		pxl += data->mlx42.s_wall->pixels[(4 * data->mlx42.s_wall->width * \
pos_in_texture) + 4 * (i * data->mlx42.s_wall->height / d) + 0] * 0x1000000;
		if (top.y + i >= 0 && top.y + i < WINDOW_HEIGHT)
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
	uint32_t	pxl;
	t_int_p2	top;
	int			pos_in_texture;
	int			pos_in_wall;

	i = 0;
	pos_in_wall = loc.y % SPRITE_SIZE;
	if (d < 0 || x < 0 || x > (int)data->mlx42.mm_player_img->width)
		return ;
	top.y = (WINDOW_HEIGHT / 2) - (d / 2);
	pos_in_texture = data->mlx42.w_wall->height * pos_in_wall / SPRITE_SIZE;
	while (i < d)
	{
		pxl = TRA_Y;
		pxl += data->mlx42.w_wall->pixels[(4 * data->mlx42.w_wall->width * \
pos_in_texture) + 4 * (i * data->mlx42.w_wall->height / d) + 2] * 0x0000100;
		pxl += data->mlx42.w_wall->pixels[(4 * data->mlx42.w_wall->width * \
pos_in_texture) + 4 * (i * data->mlx42.w_wall->height / d) + 1] * 0x0010000;
		pxl += data->mlx42.w_wall->pixels[(4 * data->mlx42.w_wall->width * \
pos_in_texture) + 4 * (i * data->mlx42.w_wall->height / d) + 0] * 0x1000000;
		if (top.y + i >= 0 && top.y + i < WINDOW_HEIGHT)
			mlx_put_pixel(data->mlx42.mm_player_img, x, top.y + i, pxl);
		i++;
	}
}
