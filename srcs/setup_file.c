/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraf <mgraf@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 22:09:37 by mgraf             #+#    #+#             */
/*   Updated: 2023/09/20 23:09:22 by mgraf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	write_rgb(int *rgb, int red, int green, int blue)
{
	if (red > 255 || green > 255 || blue > 255)
	{
		ft_putstr_fd("Invalid value for RGB color provided.\n", 1);
		return (1);
	}
	rgb[0] = red;
	rgb[1] = green;
	rgb[2] = blue;
	return (0);
}

int	init_data(t_data *data)
{
	data->mlx = NULL;
	data->start.dir = 0;
	data->start.x = 0;
	data->start.y = 0;
	data->maze = NULL;
	data->textures.n_path = NULL;
	data->textures.e_path = NULL;
	data->textures.s_path = NULL;
	data->textures.w_path = NULL;
	write_rgb(data->textures.ceiling_rgb, 0, 0, 255);
	write_rgb(data->textures.floor_rgb, 0, 255, 0);
	data->dim.lines = 0;
	data->dim.llen_head = NULL;
	data->dim.min_x = 0;
	data->dim.min_y = 0;
	data->dim.max_x = 0;
	data->dim.max_y = 0;
	data->fd = -1;
	return (0);
}

int	setup_file(t_data *data, char **av)
{
	char	*buffer;
	char	*line;

	(void)av; // temp
	init_data(data);
	data->fd = open(av[1], O_RDONLY);
	buffer = get_next_line(data->fd);
	printf("%s\n", buffer);
	free(buffer);
	close(data->fd);
	return (0);
}
