/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:10:50 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 17:00:01 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * in the top down view it draws the red and blue lines that intersect the wall
 * @param data t_data pointer
 * @param angle angle in radiant
*/
void	ray(t_data *data, double angle)
{
	t_int_p2	q;
	t_int_p2	p;
	double		dist_to_q;
	double		dist_to_p;

	q = horizontal_ray_collision(data, angle);
	p = vertical_ray_collision(data, angle);
	dist_to_p = dist((t_int_p2){data->start.x, data->start.y}, p);
	dist_to_q = dist((t_int_p2){data->start.x, data->start.y}, q);
	if (dist_to_p >= dist_to_q || isnan(dist_to_p) == 1)
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, q, L_BLUE);
	else if (dist_to_p < dist_to_q || isnan(dist_to_q) == 1)
	{
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, p, L_RED);
	}
	else if (p.x == 0 && p.y == 0)
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, p, YELLOW);
	else if (q.x == 0 && q.y == 0)
		draw_line(data, (t_int_p2){data->start.x, data->start.y}, p, YELLOW);
	else
		draw_line(data, (t_int_p2){100, 100}, (t_int_p2){400, 400}, YELLOW);
}

/**
 * sets all pixels in the mm_player_img to zero (clears image of all
 * previously written pixels)
 * @param data the t_data pointer
*/
void	clear_image(t_data *data)
{
	ft_memset(data->mlx42.mm_player_img->pixels, 0x00, sizeof(uint8_t) * \
		WINDOW_HEIGHT * WINDOW_WIDTH * 4);
}

/**
 * deletes four mlx textures
*/
void	delete_four_textures(mlx_texture_t *north, mlx_texture_t *east, \
	mlx_texture_t *south, mlx_texture_t *west)
{
	mlx_delete_texture(north);
	mlx_delete_texture(east);
	mlx_delete_texture(south);
	mlx_delete_texture(west);
}

/**
 * sets dim_x dim_y, sets mlx settings and calls mlx_init
 @param data the t_data pointer
*/
int	start_mlx(t_data *data)
{
	set_dim(data);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->mlx42.mlx_ptr = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	if (data->mlx42.mm_floor_img == NULL)
		return (1);
	return (0);
}

/**
 * @param data the t_data pointer
*/
	// check_for_tile(data, draw_floor);
	// check_for_tile(data, which_picture);
	// load_pics(data); // can fail
	// if (!ret)
	// 	ret = create_tiny_map(data);
int	render_map(t_data *data)
{
	int	ret;

	ret = start_mlx(data);
	if (!ret)
		ret = create_wall_images(data);
	if (!ret)
		ret = create_floor_ceiling_image(data);
	if (!ret)
		ret = create_image_player(data);
	if (!ret)
	{
		add_hooks(data);
		mlx_loop(data->mlx42.mlx_ptr);
	}
	mlx_close_window(data->mlx42.mlx_ptr);
	mlx_terminate(data->mlx42.mlx_ptr);
	return (0);
}
