/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_load_fill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:59:11 by mgraf             #+#    #+#             */
/*   Updated: 2023/10/14 16:59:53 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	load_texture(mlx_t *mlx, mlx_image_t **image, char *path)
{
	xpm_t	*texture;

	texture = mlx_load_xpm42(path);
	*image = mlx_texture_to_image(mlx, &texture->texture);
	mlx_delete_texture(&texture->texture);
}

void	load_pics(t_data *data)
{
	load_texture(data->mlx42.mlx_ptr, &(data->mlx42.mm_black_img), \
		"textures/minimap/mm_black_64x64.xpm42");
	load_texture(data->mlx42.mlx_ptr, &(data->mlx42.mm_grey_img), \
		"textures/minimap/mm_grey_64x64.xpm42");
	load_texture(data->mlx42.mlx_ptr, &(data->mlx42.mm_white_img), \
		"textures/minimap/mm_white_64x64.xpm42");
}

/**
 * fills the ceiling image with the ceiling color
 * @param data the t_data pointer
*/
void	fill_ceiling(t_data *data)
{
	int	i;
	int	j;
	int	height;
	int	width;
	int	color;

	i = 0;
	j = 0;
	height = WINDOW_HEIGHT / 2;
	width = WINDOW_WIDTH;
	color = TRA_Y + \
		data->textures.ceiling_rgb[2] * 0x100 + \
		data->textures.ceiling_rgb[1] * 0x10000 + \
		data->textures.ceiling_rgb[0] * 0x1000000;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			mlx_put_pixel(data->mlx42.mm_ceiling_img, i, j, color);
			i++;
		}
		j++;
	}
}

/**
 * fills the floor image with the floor color
 * @param data the t_data pointer
*/
void	fill_floor(t_data *data)
{
	int	i;
	int	j;
	int	height;
	int	width;
	int	color;

	height = WINDOW_HEIGHT / 2;
	width = WINDOW_WIDTH;
	i = 0;
	j = 0;
	color = TRA_Y + \
		data->textures.floor_rgb[2] * 0x100 + \
		data->textures.floor_rgb[1] * 0x10000 + \
		data->textures.floor_rgb[0] * 0x1000000;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			mlx_put_pixel(data->mlx42.mm_floor_img, i, j, color);
			i++;
		}
		j++;
	}
}

/**
 * sets the values of data->dim.dim_x and data->dim.dim_y
 * @param data the t_data pointer
*/
void	set_dim(t_data *data)
{
	data->dim.dim_x = data->dim.max_x - data->dim.min_x + 1;
	data->dim.dim_y = data->dim.max_y - data->dim.min_y + 1;
}
