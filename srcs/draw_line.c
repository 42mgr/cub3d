/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fheld <fheld@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:45:21 by fheld             #+#    #+#             */
/*   Updated: 2023/10/01 17:08:48 by fheld            ###   ########.fr       */
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
		// *((int *) data + (a.y + (d.y * i / d.x)) * (sl / 4) + a.x + i) = \
			// 0xffffff;
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
		// *((int *) data + (a.y + i) * (sl / 4) + a.x + (d.x * i / d.y)) = \
			// 0xffffff;
		i += inc;
	}
}

// initially just draws fixed line
void draw_line(t_data *data, t_int_p2 a, t_int_p2 b, int color)
{
	if ((b.x - a.x) == 0 && (b.y - a.y) == 0)
		mlx_put_pixel(data->mlx42.mm_player_img, a.x, a.y, color);
	else if (abs1(b.x - a.x) > abs1 (b.y - a.y))
		draw_line_case_a(data, a, b, color);
	else if (abs1(b.x - a.x) <= abs1 (b.y - a.y))
		draw_line_case_b(data, a, b, color);
}