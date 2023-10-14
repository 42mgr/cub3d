/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:42:04 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 16:43:01 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	truncate_coordinates2(t_data *data, t_int_p2 *a)
{
	if (a->x > (data->dim.max_x - data->dim.min_x) * SPRITE_SIZE)
		a->x = (data->dim.max_x - data->dim.min_x) * SPRITE_SIZE;
	if (a->x < 0)
		a->x = 0;
	if (a->y > (data->dim.max_y - data->dim.min_y) * SPRITE_SIZE)
		a->y = (data->dim.max_y - data->dim.min_y) * SPRITE_SIZE;
	if (a->y < 0)
		a->y = 0;
}

int	point_in_window(t_data *data, t_int_p2 *a)
{
	if (a->x > data->dim.dim_x * SPRITE_SIZE || a->x < 0 || \
		a->y > data->dim.dim_y * SPRITE_SIZE || a->y < 0)
		return (0);
	else
		return (1);
}

void	truncate_coordinates(t_data *data, t_int_p2 *p)
{
	if (point_in_window(data, p) == 0)
	{
		*p = (t_int_p2){50, 50};
	}
}

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
