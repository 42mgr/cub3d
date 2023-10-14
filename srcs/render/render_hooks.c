/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:57:06 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 16:57:52 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/**
 * ensures that the window is closed when ESC is pressed
 * @param arg void pointer to the mlx_t instance
*/
void	esc_hook(void *arg)
{
	mlx_t	*mlx;

	mlx = arg;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	add_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx42.mlx_ptr, esc_hook, data->mlx42.mlx_ptr);
	mlx_loop_hook(data->mlx42.mlx_ptr, move_player, data);
	mlx_loop_hook(data->mlx42.mlx_ptr, draw_player, data);
	mlx_loop_hook(data->mlx42.mlx_ptr, draw_game, data);
}
