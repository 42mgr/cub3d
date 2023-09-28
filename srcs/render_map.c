/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:10:50 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/28 15:22:33 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_map(t_data *data)
{
	data->mlx = mlx_init((data->dim.max_x - data->dim.min_x) * SPRITE_SIZE,
			(data->dim.max_y - data->dim.min_y) * SPRITE_SIZE, "Cub3D", true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_loop(data->mlx);
	mlx_close_window(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
