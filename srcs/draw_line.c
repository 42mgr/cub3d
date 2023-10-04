/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:45:21 by fheld             #+#    #+#             */
/*   Updated: 2023/10/03 18:24:22 by fheld            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * for an int x it returns the positive value
 * e.g. abs1(-14) = 14, abs1(93) = 93
*/
int	abs1(int x)
{
	if (x >= 0)
		return (x);
	return (-x);
}

void	draw_line_case_a(t_data *data, t_int_p2 a, t_int_p2 b, int color)
{
	int			i;
	int			inc;
	t_int_p2	d;

	i = 0;
	inc = 1;
	d = (t_int_p2){.x = b.x - a.x, .y = b.y - a.y};
	if (d.x == 0)
		return ;
	if (d.x < 0)
		inc = -1;
	while (abs1(i) < abs1(d.x))
	{
		mlx_put_pixel(data->mlx42.mm_player_img, a.x + i, a.y + (d.y * i / d.x), color);
		i += inc;
	}
}

void	draw_line_case_b(t_data *data, t_int_p2 a, t_int_p2 b, int color)
{
	int			i;
	int			inc;
	t_int_p2	d;

	i = 0;
	inc = 1;
	d = (t_int_p2){.x = b.x - a.x, .y = b.y - a.y};
	if (d.y == 0)
		return ;
	if (d.y < 0)
		inc = -1;
	while (abs1(i) < abs1(d.y))
	{
		mlx_put_pixel(data->mlx42.mm_player_img, \
			a.x + (d.x * i / d.y), a.y + i, color);
		i += inc;
	}
}

void	truncate_coordinates2(t_data *data, t_int_p2 *a)
{
	if (a->x > (data->dim.max_x - data->dim.min_x)* SPRITE_SIZE)
		a->x = (data->dim.max_x - data->dim.min_x) * SPRITE_SIZE;
	if (a->x < 0)
		a->x = 0;
	if (a->y > (data->dim.max_y - data->dim.min_y)* SPRITE_SIZE)
		a->y = (data->dim.max_y - data->dim.min_y) * SPRITE_SIZE;
	if (a->y < 0)
		a->y = 0;
}

void	truncate_coordinates(t_data *data, t_int_p2 *a)
{
	if (a->x > data->dim.dim_x * SPRITE_SIZE || \
		a->x < 0 || \
		a->y > data->dim.dim_y * SPRITE_SIZE || \
		a->y < 0)
		*a = (t_int_p2){0, 0};
}

/**
 * draws line from point a to point b with color
 * if a or b have coordinated that are out of the image they are truncated
*/
void draw_line(t_data *data, t_int_p2 a, t_int_p2 b, int color)
{
	truncate_coordinates(data, &a);
	truncate_coordinates(data, &b);
	if ((b.x - a.x) == 0 && (b.y - a.y) == 0)
		mlx_put_pixel(data->mlx42.mm_player_img, a.x, a.y, color);
	else if (abs1(b.x - a.x) > abs1 (b.y - a.y))
		draw_line_case_a(data, a, b, color);
	else if (abs1(b.x - a.x) <= abs1 (b.y - a.y))
		draw_line_case_b(data, a, b, color);
}